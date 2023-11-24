/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/24 18:33:21 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	handle_redirections_for_child(t_node *node, t_redirects *redirects);
void	free_redirects(t_redirects *redirects);
void	free_node(t_node *node);
void	free_info(t_info *info);
void	free_info_token(t_info *info);

void	exec_left_node(t_info info, char **envp, t_node *node, int *pipefd)
{
	close(pipefd[PIPE_READ]);
	ft_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close(pipefd[PIPE_WRITE]);
	if (node != NULL)
		child_process(info, envp, node);
	exit(2);
}

void	exec_right_node(t_info info, char **envp, t_node *node, int *pipefd)
{
	close(pipefd[PIPE_WRITE]);
	ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close(pipefd[PIPE_READ]);
	if (node != NULL)
		child_process(info, envp, node);
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
		exec_left_node(info, envp, node->left, pipefd);
		exit(1);
	}
	parent2 = ft_fork();
	if (parent2 == 0)
	{
		exec_right_node(info, envp, node->right, pipefd);
		exit(1);
	}
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
	waitpid(parent1, NULL, 0);
	waitpid(parent2, NULL, 0);
}

void	child_process(t_info info, char **envp, t_node *node)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = ft_dup(STDIN_FILENO);
	stdout_backup = ft_dup(STDOUT_FILENO);
	if (node == NULL)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(info, envp, node);
	else
	{
		handle_redirections_for_child(node, node->redirects);
		ft_exec(node->data, envp, &info, node);
	}
	ft_dup2(stdin_backup, STDIN_FILENO);
	ft_dup2(stdout_backup, STDOUT_FILENO);
}

void	parse(char *line, t_info *info, char **envp)
{
	t_node	*node;

	info->token = ft_split(line, ' ');
	node = parser(lexer_main(line));
	// printf("0:[%s], 1:[%s]\n", node->data[0], node->data[1]);
	child_process(*info, envp, node);
	free_info_token(info);
	free_node(node);
}
