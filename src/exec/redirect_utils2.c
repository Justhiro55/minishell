/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:45:07 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/22 12:49:51 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	here_doc(char *delimiter);

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
	pid_t		parent;
	t_redirects	*tmp;

	tmp = redirects;
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
