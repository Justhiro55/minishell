/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:45:07 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/01/12 17:37:18 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	here_doc(char *delimiter);
void	expand_variable(t_node *node, t_info *info);
int		exec_left_node(t_info *info, char **envp, t_node *node, int *pipefd);
int		exec_right_node(t_info *info, char **envp, t_node *node, int *pipefd);

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

void	here_doc_fork(t_redirects *redirects)
{
	pid_t	parent;

	parent = fork();
	if (!parent)
	{
		here_doc_mock(redirects->filename);
		exit(0);
	}
}

void	restore_stdin_stdout(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != STDIN_FILENO)
		ft_dup2(stdin_backup, STDIN_FILENO);
	if (stdout_backup != STDOUT_FILENO)
		ft_dup2(stdout_backup, STDOUT_FILENO);
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
		if (exec_right_node(info, envp, node->right, pipefd) == 1)
			exit(1);
		exit(0);
	}
	close(pipefd[PIPE_READ]);
	close(pipefd[PIPE_WRITE]);
	waitpid(parent1, NULL, 0);
	waitpid(parent2, &status, 0);
	return (status);
}
