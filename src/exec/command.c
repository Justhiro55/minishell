/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/18 15:35:58 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	handle_redirections_for_child(t_node *node, t_redirects *redirects);
void	free_redirects(t_redirects *redirects);
void	free_node(t_node *node);
void	free_info(t_info *info);

void	exec_left_node(t_info *info, char **envp, t_node *node, int *pipefd)
{
	int	status;

	status = 0;
	close(pipefd[PIPE_READ]);
	ft_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO);
	close(pipefd[PIPE_WRITE]);
	if (node != NULL)
		status = child_process(info, envp, node);
	exit(status);
}

void	exec_right_node(t_info *info, char **envp, t_node *node, int *pipefd)
{
	int	status;

	status = 0;
	close(pipefd[PIPE_WRITE]);
	ft_dup2(pipefd[PIPE_READ], STDIN_FILENO);
	close(pipefd[PIPE_READ]);
	if (node != NULL)
		status = child_process(info, envp, node);
	exit(status);
}

int	exec_pipe(t_info *info, char **envp, t_node *node)
{
	int		pipefd[2];
	pid_t	parent1;
	pid_t	parent2;
	int		status;

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
		wait(NULL);
		exec_right_node(info, envp, node->right, pipefd);
		exit(0);
	}
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
	waitpid(parent1, NULL, 0);
	waitpid(parent2, &status, 0);
	return (status);
}

void	expand_variable(t_node *node, t_info *info);

int	child_process(t_info *info, char **envp, t_node *node)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	stdin_backup = ft_dup(STDIN_FILENO);
	stdout_backup = ft_dup(STDOUT_FILENO);
	status = 0;
	if (node == NULL)
		return (1);
	if (node->type == NODE_PIPE)
		status = exec_pipe(info, envp, node);
	else
	{
		expand_variable(node, info);
		handle_redirections_for_child(node, node->redirects);
		if (g_signal != SIGINT)
			status = ft_exec(node->data, envp, info, node);
	}
	ft_dup2(stdin_backup, STDIN_FILENO);
	ft_dup2(stdout_backup, STDOUT_FILENO);
	return (status);
}

void	parse(char *line, t_info *info, char **envp)
{
	t_tokeniser	*tokeniser;
	t_node		*node;

	tokeniser = init_tokeniser();
	node = parser(lexer_main(line, tokeniser));
	add_history(line);
	free(line);
	info->status = child_process(info, envp, node);
	free_node(node);
}
