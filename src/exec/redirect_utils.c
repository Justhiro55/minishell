/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:07:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/01/10 12:33:04 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	remove_quotes(char *str);

int	open_file(t_redirects *redirects)
{
	int	status;

	status = -1;
	if (redirects == NULL)
		return (status);
	if (redirects->filename != NULL && redirects->filename[0] != '\0')
		remove_quotes(redirects->filename);
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
		exit(1);
	return (new_fd);
}

int	ft_dup2(int old_fd, int new_fd)
{
	if (old_fd == new_fd)
		return (0);
	if (dup2(old_fd, new_fd) == -1)
	{
		return (1);
	}
	return (0);
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		exit_process(1);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit_process(1);
	return (pid);
}
