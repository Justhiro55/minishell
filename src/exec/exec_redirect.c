/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:42:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/13 19:26:21 by hhagiwar         ###   ########.fr       */
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

void	here_doc_mock(char *delimiter)
{
	char	*line;

	ft_dup2(STDIN_FILENO, STDOUT_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		free(line);
	}
}

void	handle_redirections_for_child(t_node *node, t_redirects *redirects)
{
	int		status;
	int		stdin_backup;
	int		stdout_backup;
	pid_t	parent;

	stdin_backup = STDIN_FILENO;
	stdout_backup = STDOUT_FILENO;
	while (redirects->next != NULL)
	{
		if (redirects->type == REDIRECT_HEREDOC && redirects->next != NULL)
		{
			parent = fork();
			if (!parent)
			{
				here_doc_mock(redirects->filename);
				exit(1);
			}
			else
				wait(&status);
		}
		if (redirects != NULL && node->type == NODE_COMMAND
			&& redirects->type == REDIRECT_INPUT)
			ft_dup2(redirects->fd_file, STDIN_FILENO);
		if (redirects != NULL && node->type == NODE_COMMAND
			&& redirects->type == REDIRECT_OUTPUT)
			ft_dup2(redirects->fd_file, STDOUT_FILENO);
		redirects = redirects->next;
	}
	if (redirects != NULL && node->type == NODE_COMMAND
		&& redirects->type == REDIRECT_INPUT)
		ft_dup2(redirects->fd_file, STDIN_FILENO);
	if (redirects != NULL && node->type == NODE_COMMAND
		&& redirects->type == REDIRECT_OUTPUT)
		ft_dup2(redirects->fd_file, STDOUT_FILENO);
	ft_dup2(stdin_backup, STDIN_FILENO);
	ft_dup2(stdout_backup, STDOUT_FILENO);
	if (redirects != NULL && node->type == NODE_COMMAND
		&& redirects->type == REDIRECT_HEREDOC)
		here_doc(redirects->filename);
}

void	execute_child_process(t_info info, char **envp, t_node *node, int *fd)
{
	int			fd_backup;
	t_redirects	*redirects;

	(void)fd;
	ft_dup2(fd[1], STDOUT_FILENO);
	if (ft_strcmp(node->left->data[0], "pipe") == 0)
		child_process(info, envp, node->left);
	else
	{
		redirects = node->redirects;
		fd_backup = dup(STDOUT_FILENO);
		redirects = node->left->redirects;
		handle_redirections_for_child(node->left, redirects);
		ft_dup2(fd_backup, STDOUT_FILENO);
		ft_exec(node->left->data, envp, &info, node);
	}
}

void	handle_redirections_for_parent(t_node *node)
{
	while (node->right->redirects->next != NULL)
	{
		if (node->right->redirects->type == REDIRECT_OUTPUT
			|| node->right->redirects->type == REDIRECT_APPEND_OUTPUT)
			open_file(node->right->redirects);
		node->right->redirects = node->right->redirects->next; //
	}
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
