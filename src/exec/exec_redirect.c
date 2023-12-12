/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/12 17:37:52 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	here_doc(char *delimiter, int pipefd[2])
{
	char	*line;
	int		stdout_backup;

	stdout_backup = ft_dup(STDOUT_FILENO);
	while (1)
	{
		ft_dup2(STDIN_FILENO, STDOUT_FILENO);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[PIPE_WRITE], line, ft_strlen(line));
		write(pipefd[PIPE_WRITE], "\n", 1);
		free(line);
	}
	ft_dup2(stdout_backup, STDOUT_FILENO);
	wait(NULL);
	return (1);
}

int	update_stdin(int *stdin_backup, t_redirects *redirects)
{
	*stdin_backup = open_file(redirects);
	return (0);
}

void	set_redirects(int stdin_backup, int stdout_backup, int pipefd[2],
		int heredoc_flag)
{
	if (heredoc_flag == 0)
		ft_dup2(stdin_backup, STDIN_FILENO);
	else
		ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	ft_dup2(stdout_backup, STDOUT_FILENO);
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
}

void	handle_redirections_for_child(t_node *node, t_redirects *redirects)
{
	int	stdin_backup;
	int	stdout_backup;
	int	pipefd[2];
	int	heredoc_flag;

	heredoc_flag = 0;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	ft_pipe(pipefd);
	while (redirects != NULL && node->type == NODE_COMMAND)
	{
		ft_dup2(redirects->fd_backup, STDIN_FILENO);
		if (redirects->type == REDIRECT_INPUT)
			heredoc_flag = update_stdin(&stdin_backup, redirects);
		else if (redirects->type == REDIRECT_OUTPUT
			|| redirects->type == REDIRECT_APPEND_OUTPUT)
			stdout_backup = open_file(redirects);
		else if (redirects->type == REDIRECT_HEREDOC)
		{
			ft_pipe(pipefd);
			heredoc_flag = here_doc(redirects->filename, pipefd);
		}
		redirects = redirects->next;
	}
	set_redirects(stdin_backup, stdout_backup, pipefd, heredoc_flag);
}
