/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:07:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/09 18:59:40 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	open_file(t_node *node)
{
	if (node == NULL || node->redirects == NULL)
		return (-1);
	if (node->redirects->type == REDIRECT_INPUT)
		return (open(node->redirects->filename, O_RDONLY, 0));
	if (node->redirects->type == REDIRECT_OUTPUT)
		return (open(node->redirects->filename, O_WRONLY | O_CREAT | O_TRUNC,
				0644));
	if (node->redirects->type == REDIRECT_APPEND_OUTPUT)
		return (open(node->redirects->filename, O_WRONLY | O_CREAT | O_APPEND,
				0644));
	return (-1);
}

int	ft_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
		exit_process(EXIT_FAILURE_DUP);
	return (new_fd);
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (old_fd == new_fd)
		return ;
	if (dup2(old_fd, new_fd) == -1)
		exit_process(EXIT_FAILURE_DUP);
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		exit_process(EXIT_FAILURE_PIPE);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_process(EXIT_FAILURE_FILE);
	return (pid);
}
