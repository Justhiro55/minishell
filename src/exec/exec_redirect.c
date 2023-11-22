/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/22 14:09:41 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	here_doc(char *delimiter, int pipefd[2])
{
	char	*line;
	int		stdout_backup;

	(void)stdout_backup;
	(void)pipefd;
	// ft_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	while (1)
	{
		stdout_backup = ft_dup(STDOUT_FILENO);
		ft_dup2(STDIN_FILENO, STDOUT_FILENO);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			// exit(1);
			break ;
		}
		ft_dup2(stdout_backup, STDOUT_FILENO);
		write(pipefd[PIPE_WRITE], line, ft_strlen(line));
		write(pipefd[PIPE_WRITE], "\n", 1);
		free(line);
		// exit(1);
	}
}

void	handle_redirections_for_child(t_node *node, t_redirects *redirects)
{
	int	stdin_backup;
	int	stdout_backup;
	int	pipefd[2];
	int	heredoc_flag;

	// t_redirects	*tmp;
	heredoc_flag = 0;
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	pipe(pipefd);
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

// void	execute_child_process(t_info info, char **envp, t_node *node, int *fd)
// {
// 	pid_t	parent;

// 	parent = ft_fork();
// 	if (!parent)
// 	{
// 		ft_dup2(fd[PIPE_WRITE], STDOUT_FILENO);
// 		if (ft_strcmp(node->data[0], "pipe") == 0)
// 			child_process(info, envp, node);
// 		else
// 		{
// 			handle_redirections_for_child(node, node->redirects);
// 			wait(NULL);
// 			ft_exec(node->data, envp, &info, node);
// 		}
// 		exit(0);
// 	}
// }
