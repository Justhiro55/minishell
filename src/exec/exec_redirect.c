/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/22 18:35:27 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	here_doc(char *delimiter, int pipefd[2])
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
		if (redirects->type == REDIRECT_INPUT)
		{
			stdin_backup = open_file(redirects);
			heredoc_flag = 0;
		}
		else if (redirects->type == REDIRECT_OUTPUT
			|| redirects->type == REDIRECT_APPEND_OUTPUT)
			stdout_backup = open_file(redirects);
		else if (redirects->type == REDIRECT_HEREDOC)
		{
			ft_pipe(pipefd);
			ft_dup2(redirects->fd_backup, STDIN_FILENO);
			here_doc(redirects->filename, pipefd);
			heredoc_flag = 1;
		}
		redirects = redirects->next;
	}
	if (heredoc_flag == 0)
		ft_dup2(stdin_backup, STDIN_FILENO);
	else
		ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	ft_dup2(stdout_backup, STDOUT_FILENO);
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
}
