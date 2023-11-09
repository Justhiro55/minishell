/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/09 18:35:03 by hhagiwar         ###   ########.fr       */
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

void	handle_redirections_for_child(t_node *node)
{
	int	stdin_backup;
	int	fd[2];

	if (node->redirects != NULL && node->type == NODE_COMMAND
		&& node->redirects->fd_file > 0
		&& node->redirects->type == REDIRECT_INPUT)
		ft_dup2(node->redirects->fd_file, STDIN_FILENO);
	if (node->redirects != NULL && node->type == NODE_COMMAND
		&& node->redirects->fd_file > 0
		&& node->redirects->type == REDIRECT_OUTPUT)
		ft_dup2(node->redirects->fd_file, STDIN_FILENO);
	if (node->redirects != NULL && node->type == NODE_COMMAND
		&& node->redirects->type == REDIRECT_HEREDOC)
	{
		stdin_backup = ft_dup(STDIN_FILENO);
		ft_pipe(fd);
		here_doc(node->redirects->filename);
		ft_dup2(fd[PIPE_READ], STDIN_FILENO);
		close(fd[PIPE_READ]);
		close(fd[PIPE_WRITE]);
		ft_dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
}

void	execute_child_process(t_info info, char **envp, t_node *node, int *fd)
{
	int	fd_backup;

	fd_backup = dup(STDOUT_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	if (ft_strcmp(node->left->data[0], "pipe") == 0)
		child_process(info, envp, node->left);
	else
	{
		handle_redirections_for_child(node->left);
		ft_exec(node->left->data, envp, &info, node);
	}
}

void	handle_redirections_for_parent(t_node *node)
{
	if (node->right->redirects != NULL && node->right->type == NODE_COMMAND
		&& node->right->redirects->fd_file > 0
		&& node->right->redirects->type == REDIRECT_OUTPUT)
		ft_dup2(node->right->redirects->fd_file, STDOUT_FILENO);
	if (node->right->redirects != NULL && node->right->type == NODE_COMMAND
		&& node->right->redirects->fd_file > 0
		&& node->right->redirects->type == REDIRECT_INPUT)
		ft_dup2(node->right->redirects->fd_file, STDIN_FILENO);
}

void	execute_parent_process(t_info info, char **envp, t_node *node, int *fd)
{
	int	status;

	close(fd[1]);
	ft_dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	handle_redirections_for_parent(node);
	ft_exec(node->right->data, envp, &info, node);
	wait(&status);
}
