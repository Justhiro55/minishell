/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/09 20:18:56 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	create_fork_and_execute_child(t_info info, char **envp, t_node *node,
		int *fd)
{
	pid_t	parent;

	parent = ft_fork();
	if (!parent)
	{
		execute_child_process(info, envp, node, fd);
		exit(0);
	}
}

void	child_process(t_info info, char **envp, t_node *node)
{
	int		fd[2];
	pid_t	parent;
	int		status;

	parent = ft_fork();
	ft_pipe(fd);
	if (!parent)
	{
		create_fork_and_execute_child(info, envp, node, fd);
		execute_parent_process(info, envp, node, fd);
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
