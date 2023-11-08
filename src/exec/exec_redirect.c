/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/08 19:13:04 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	write_to_pipe(int fd[2], char *delimiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(fd[1]);
			exit(EXIT_SUCCESS);
		}
		// 標準出力をターミナルに戻す
		dup2(STDOUT_FILENO, 1);
		// write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		// 標準出力を再びパイプに戻す
		dup2(fd[1], STDOUT_FILENO);
	}
}

void	here_doc(char *delimiter)
{
	int		fd[2];
	pid_t	parent;

	if (pipe(fd) == -1)
		exit_process(EXIT_FAILURE_PIPE);
	parent = fork();
	if (parent < 0)
		exit_process(EXIT_FAILURE_FORK);
	if (!parent)
	{
		close(fd[0]);
		write_to_pipe(fd, delimiter);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	handle_redirections_for_child(t_node *node)
{
	if (node->redirects != NULL && node->type == NODE_COMMAND
		&& node->redirects->fd_file > 0
		&& node->redirects->type == REDIRECT_INPUT)
		dup2(node->redirects->fd_file, STDIN_FILENO);
	if (node->redirects != NULL && node->type == NODE_COMMAND
		&& node->redirects->fd_file > 0
		&& node->redirects->type == REDIRECT_OUTPUT)
		dup2(node->redirects->fd_file, STDIN_FILENO);
	if (node->redirects != NULL && node->type == NODE_COMMAND
		&& node->redirects->type == REDIRECT_HEREDOC)
	{
		here_doc(node->redirects->filename);
	}
}

void	execute_child_process(t_info info, char **envp, t_node *node, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (ft_strcmp(node->left->data[0], "pipe") == 0)
	{
		child_process(info, envp, node->left);
	}
	else
	{
		handle_redirections_for_child(node->left);
		ft_exec(node->left->data, envp, &info);
	}
}

void	handle_redirections_for_parent(t_node *node)
{
	if (node->right->redirects != NULL && node->right->type == NODE_COMMAND
		&& node->right->redirects->fd_file > 0
		&& node->right->redirects->type == REDIRECT_OUTPUT)
		dup2(node->right->redirects->fd_file, STDOUT_FILENO);
	// if (node->right->redirects != NULL && node->right->type == NODE_COMMAND
	// 	&& node->right->redirects->fd_file > 0
	// 	&& node->right->redirects->type == REDIRECT_INPUT)
	// 	dup2(node->right->redirects->fd_file, STDIN_FILENO);
}

void	execute_parent_process(t_info info, char **envp, t_node *node, int *fd)
{
	int	status;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	handle_redirections_for_parent(node);
	ft_exec(node->right->data, envp, &info);
	wait(&status);
}
