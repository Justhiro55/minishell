/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/26 10:09:00 by hhagiwar         ###   ########.fr       */
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
		change_signal(1);
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
	if (ft_dup2(stdout_backup, STDOUT_FILENO) == 1)
		return (1);
	wait(NULL);
	return (1);
}

int	update_stdin(int *stdin_backup, t_redirects *redirects)
{
	*stdin_backup = open_file(redirects);
	return (0);
}

int	set_redirects(int stdin_backup, int stdout_backup, int pipefd[2],
		int heredoc_flag)
{
	if (heredoc_flag == 0)
	{
		if (ft_dup2(stdin_backup, STDIN_FILENO) == 1)
			return (1);
	}
	else
	{
		if (ft_dup2(pipefd[PIPE_READ], STDIN_FILENO) == 1)
			return (1);
	}
	ft_dup2(stdout_backup, STDOUT_FILENO);
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
	return (0);
}

void	init_redirections(int *heredoc_flag, int *stdio_backup,
		int *stdout_backup)
{
	*heredoc_flag = 0;
	*stdio_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
}

int	handle_redirections_for_child(t_node *node, t_redirects *redirects)
{
	int	stdin_backup;
	int	stdout_backup;
	int	pipefd[2];
	int	heredoc_flag;

	init_redirections(&heredoc_flag, &stdin_backup, &stdout_backup);
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
		if (g_signal == SIGINT || stdin_backup == -1 || stdout_backup == -1)
			return (1);
	}
	return (set_redirects(stdin_backup, stdout_backup, pipefd, heredoc_flag));
}
