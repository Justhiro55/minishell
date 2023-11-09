/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:07:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/09 17:23:37 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

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
