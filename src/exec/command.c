/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/14 18:10:03 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	handle_redirections_for_child(t_node *node, t_redirects *redirects);

void	child_process(t_info info, char **envp, t_node *node)
{
	int		fd[2];
	pid_t	parent;
	int		status;

	ft_pipe(fd);
	parent = ft_fork();
	if (!parent)
	{
		execute_child_process(info, envp, node->left, fd);
		wait(&status);
		execute_child_process(info, envp, node->right, fd);
		wait(&status);
		exit(0);
	}
	wait(&status);
	return ;
}

int		i = 0;

void	parse(char *line, t_info *info, char **envp)
{
	t_node	*node;

	set_token(info, line);
	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		exit_process(EXIT_FAILURE_MALLOC);
	if (i == 0)
		set_node(node); //test用
	if (node != NULL && node->type == NODE_PIPE && i == 0)
	{
		child_process(*info, envp, node);
		i++;
	}
	else
		ft_exec(info->token, envp, info, node);
}
