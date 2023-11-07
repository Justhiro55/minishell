/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/07 15:26:38 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exit_process(int status)
{
	if (status == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (status == EXIT_FAILURE_FILE)
	{
		perror("File open error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_FORK)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_MALLOC)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_PIPE)
	{
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
}

void	create_fork_and_execute_child(t_info info, char **envp, t_node *node,
		int *fd)
{
	pid_t	parent;

	parent = fork();
	if (parent == -1)
		exit_process(EXIT_FAILURE_FORK);
	else if (!parent)
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

	parent = fork();
	if (pipe(fd) == -1)
		exit_process(EXIT_FAILURE_PIPE);
	else if (!parent)
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
		ft_exec(info->token, envp, info);
}
