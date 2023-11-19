/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/18 19:01:43 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	here_doc(char *delimiter, int pipefd[2])
{
	int		fd[2];
	pid_t	parent;
	char	*line;
	int		stdout_backup;

	if (pipe(fd) == -1)
		exit_process(EXIT_FAILURE_PIPE);
	parent = fork();
	if (parent < 0)
		exit_process(EXIT_FAILURE_FORK);
	if (!parent)
	{
		close(fd[0]);
		ft_dup2(fd[1], STDOUT_FILENO);
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
				exit(1);
			}
			ft_dup2(stdout_backup, STDOUT_FILENO);
			write(STDOUT_FILENO, line, ft_strlen(line));
			write(STDOUT_FILENO, "\n", 1);
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(parent, NULL, 0);
	}
	(void)pipefd;
}

void	handle_redirections_for_child(t_node *node, t_redirects *redirects)
{
	t_redirects	*tmp;
	t_redirects	*re;
	int			stdin_backup;
	int			stdout_backup;
	int			pipefd[2];
	int			heredoc_flag;

	re = redirects;
	heredoc_flag = 0;
	stdin_backup = STDIN_FILENO;
	stdout_backup = STDOUT_FILENO;
	while (redirects != NULL && node->type == NODE_COMMAND)
	{
		if (redirects->type == REDIRECT_INPUT)
		{
			heredoc_flag = 0;
			stdin_backup = open_file(redirects);
		}
		else if (redirects->type == REDIRECT_OUTPUT
				|| redirects->type == REDIRECT_APPEND_OUTPUT)
			stdout_backup = open_file(redirects);
		else if (redirects->type == REDIRECT_HEREDOC)
		{
			tmp = redirects;
			heredoc_flag = 1;
		}
		redirects = redirects->next;
	}
	ft_dup2(stdout_backup, STDOUT_FILENO);
	if (heredoc_flag == 1)
		here_doc(tmp->filename, pipefd);
	else
		ft_dup2(stdin_backup, STDIN_FILENO);
}

void	execute_child_process(t_info info, char **envp, t_node *node, int *fd)
{
	pid_t	parent;

	parent = ft_fork();
	if (!parent)
	{
		ft_dup2(fd[PIPE_WRITE], STDOUT_FILENO);
		if (ft_strcmp(node->data[0], "pipe") == 0)
			child_process(info, envp, node);
		else
		{
			handle_redirections_for_child(node, node->redirects);
			ft_exec(node->data, envp, &info, node);
		}
		exit(0);
	}
}
