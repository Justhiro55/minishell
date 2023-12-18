/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:07:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/18 19:16:10 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	open_file(t_redirects *redirects)
{
	int	status;

	status = -1;
	if (redirects == NULL)
		return (status);
	if (redirects->type == REDIRECT_INPUT)
		status = (open(redirects->filename, O_RDONLY, 0));
	if (redirects->type == REDIRECT_OUTPUT)
		status = (open(redirects->filename, O_WRONLY | O_CREAT | O_TRUNC,
					0644));
	if (redirects->type == REDIRECT_APPEND_OUTPUT)
		status = (open(redirects->filename, O_WRONLY | O_CREAT | O_APPEND,
					0644));
	if (status == -1)
		perror(redirects->filename);
	return (status);
}

int	ft_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
		exit(EXIT_FAILURE_DUP);
	return (new_fd);
}

void	ft_dup2(int old_fd, int new_fd)
{
	if (old_fd == new_fd)
		return ;
	if (dup2(old_fd, new_fd) == -1)
		exit(EXIT_FAILURE_DUP);
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
