/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/14 19:23:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	here_doc(char *delimiter)
{
	char	*line;
	int		stdout_backup;

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
			exit(EXIT_SUCCESS);
		}
		ft_dup2(stdout_backup, STDOUT_FILENO);
		write(STDOUT_FILENO, line, ft_strlen(line));
		write(STDOUT_FILENO, "\n", 1);
		free(line);
	}
}

void	handle_redirections_for_child(t_node *node, t_redirects *redirects)
{
	int	status;
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = STDIN_FILENO;
	stdout_backup = STDOUT_FILENO;
	while (redirects != NULL && node->type == NODE_COMMAND)
	{
		if (redirects->type == REDIRECT_HEREDOC)
		{
			here_doc_fork(redirects);
			wait(&status);
		}
		else if (redirects->type == REDIRECT_INPUT)
			stdin_backup = redirects->fd_file;
		else if (redirects->type == REDIRECT_OUTPUT
			|| redirects->type == REDIRECT_APPEND_OUTPUT)
		{
			redirects->fd_file = open_file(redirects);
			stdout_backup = redirects->fd_file;
		}
		redirects = redirects->next;
	}
	restore_stdin_stdout(stdin_backup, stdout_backup);
}

void	execute_child_process(t_info info, char **envp, t_node *node, int *fd)
{
	pid_t		parent;
	int			fd_backup;
	t_redirects	*redirects;

	parent = ft_fork();
	fd_backup = 0;
	if (!parent)
	{
		ft_dup2(fd[1], STDOUT_FILENO);
		if (ft_strcmp(node->data[0], "pipe") == 0)
			child_process(info, envp, node);
		else
		{
			fd_backup = ft_dup(STDOUT_FILENO);
			redirects = node->redirects;
			handle_redirections_for_child(node, redirects);
			ft_exec(node->data, envp, &info, node);
			ft_dup2(fd_backup, STDOUT_FILENO);
		}
		exit(0);
	}
}

// void	handle_redirections_for_parent(t_node *node)
// {
// 	while (node->redirects->next != NULL)
// 	{
// 		if (node->redirects->type == REDIRECT_OUTPUT
// 			|| node->redirects->type == REDIRECT_APPEND_OUTPUT)
// 			open_file(node->redirects);
// 		node->redirects = node->redirects->next;
// 	}
// 	if (node->redirects != NULL && node->type == NODE_COMMAND
// 		&& node->redirects->fd_file > 0
// 		&& node->redirects->type == REDIRECT_OUTPUT)
// 		ft_dup2(node->redirects->fd_file, STDOUT_FILENO);
// 	if (node->redirects != NULL && node->type == NODE_COMMAND
// 		&& node->redirects->fd_file > 0
// 		&& node->redirects->type == REDIRECT_INPUT)
// 		ft_dup2(node->redirects->fd_file, STDIN_FILENO);
// }

// void	execute_parent_process(t_info info, char **envp, t_node *node, int *fd)
// {
// 	int	status;

// 	close(fd[1]);
// 	ft_dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	handle_redirections_for_parent(node->right);
// 	ft_exec(node->right->data, envp, &info, node);
// 	wait(&status);
// }
