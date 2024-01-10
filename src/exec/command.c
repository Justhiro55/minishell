/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/01/10 11:49:36 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int		handle_redirections_for_child(t_node *node, t_redirects *redirects);
void	free_redirects(t_redirects *redirects);
void	free_node(t_node *node);
void	free_info(t_info *info);
void	expand_variable(t_node *node, t_info *info);
int		exec_pipe(t_info *info, char **envp, t_node *node);

int	exec_left_node(t_info *info, char **envp, t_node *node, int *pipefd)
{
	int	status;

	status = 0;
	close(pipefd[PIPE_READ]);
	if (ft_dup2(pipefd[PIPE_WRITE], STDOUT_FILENO) == 1)
		exit(1);
	close(pipefd[PIPE_WRITE]);
	if (node != NULL)
		status = child_process(info, envp, node);
	exit(status);
}

int	exec_right_node(t_info *info, char **envp, t_node *node, int *pipefd)
{
	int	status;

	status = 0;
	close(pipefd[PIPE_WRITE]);
	if (ft_dup2(pipefd[PIPE_READ], STDIN_FILENO) == 1)
		exit(1);
	close(pipefd[PIPE_READ]);
	if (node != NULL)
		status = child_process(info, envp, node);
	exit(status);
}

void	process_exec(t_info *info, char **envp, t_node *node)
{
	int	status;

	status = 0;
	expand_variable(node, info);
	status = handle_redirections_for_child(node, node->redirects);
	if (status == 1)
	{
		info->status = 1;
		return ;
	}
	else if (status == 2)
		info->status = 0;
	if (g_signal != SIGINT && status != 2)
		info->status = ft_exec(node->data, envp, info, node) % 256;
}

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
		info->status = exec_pipe(info, envp, node) % 256;
	else
		process_exec(info, envp, node);
	ft_dup2(stdin_backup, STDIN_FILENO);
	ft_dup2(stdout_backup, STDOUT_FILENO);
	return (info->status % 256);
}

void	parse(char *line, t_info *info, char **envp)
{
	t_tokeniser	*tokeniser;
	t_node		*node;
	t_token		*token;

	tokeniser = init_tokeniser();
	token = lexer_main(line, tokeniser, info);
	if (token == NULL)
	{
		add_history(line);
		free(line);
		return ;
	}
	node = parser(token, info);
	add_history(line);
	free(line);
	info->status = child_process(info, envp, node);
	free_node(node);
}
