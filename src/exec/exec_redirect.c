/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/06 19:49:30 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	handle_redirections_for_child(t_node *node)
{
	if (node->redirects != NULL && node->type == NODE_COMMAND
		&& node->redirects->fd_file > 0)
		dup2(node->redirects->fd_file, STDIN_FILENO);
}

void	execute_child_process(t_info info, char **envp, t_node *node, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (ft_strcmp(node->left->data[0], "pipe") == 0)
		child_process(info, envp, node->left);
	else
	{
		handle_redirections_for_child(node);
		ft_exec(node->left->data, envp, &info);
	}
}

void	handle_redirections_for_parent(t_node *node)
{
	if (node->right->redirects != NULL && node->right->type == NODE_COMMAND
		&& node->right->redirects->fd_file > 0)
	{
		dup2(node->right->redirects->fd_file, STDOUT_FILENO);
	}
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
