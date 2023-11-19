/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/19 16:27:02 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	handle_redirections_for_child(t_node *node, t_redirects *redirects);

void	exec_left_node(t_info info, char **envp, t_node *node, int *pipefd)
{
	close(pipefd[PIPE_READ]);
	ft_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close(pipefd[PIPE_WRITE]);
	if (node->left != NULL)
		child_process(info, envp, node->left);
	wait(NULL);
	exit(1);
}

void	exec_right_node(t_info info, char **envp, t_node *node, int *pipefd)
{
	close(pipefd[PIPE_WRITE]);
	ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close(pipefd[PIPE_READ]);
	if (node->right != NULL)
		child_process(info, envp, node->right);
	wait(NULL);
	exit(1);
}

void	exec_pipe(t_info info, char **envp, t_node *node)
{
	int		pipefd[2];
	pid_t	parent1;
	pid_t	parent2;

	ft_pipe(pipefd);
	parent1 = ft_fork();
	if (parent1 == 0)
	{
		wait(NULL);
		exec_left_node(info, envp, node, pipefd);
	}
	parent2 = ft_fork();
	if (parent2 == 0)
	{
		wait(NULL);
		exec_right_node(info, envp, node, pipefd);
	}
	wait(NULL);
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
}

void	child_process(t_info info, char **envp, t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(info, envp, node);
	else
	{
		handle_redirections_for_child(node, node->redirects);
		wait(NULL);
		ft_exec(node->data, envp, &info, node);
	}
	exit(EXIT_SUCCESS);
}

int		i = 0;

void	parse(char *line, t_info *info, char **envp)
{
	t_node *node;

	set_token(info, line);
	if (i == 0)
	{
		node = (t_node *)malloc(sizeof(t_node));
		if (node == NULL)
			exit_process(EXIT_FAILURE_MALLOC);
		set_node(node); //test用
	}
	else
		node = parser(lexer_main(line));
	if (node != NULL && node->type == NODE_PIPE && i == 0)
	{
		pid_t parent = ft_fork();
		if (!parent)
			child_process(*info, envp, node);
		else
			waitpid(parent, NULL, 0);
		i++;
	}
	else
	{
		int fd[2];
		if (node->redirects != NULL)
		{
			pipe(fd);
			execute_child_process(*info, envp, node, fd);
			wait(NULL);
		}
		else
			ft_exec(node->data, envp, info, node);
		free(node);
	}
}