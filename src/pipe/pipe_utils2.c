/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:44:05 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/09 17:20:10 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(char ***cmd, int cmd_count)
{
	int		i;
	char	**cmd_args;
	int		j;

	i = 0;
	while (i < cmd_count)
	{
		cmd_args = cmd[i];
		j = 0;
		while (cmd_args[j] != NULL)
		{
			free(cmd_args[j]);
			j++;
		}
		free(cmd_args);
		i++;
	}
	free(cmd);
}

void	free_fd(int **pipefd, int pipe_num)
{
	int	i;

	i = 0;
	while (i < pipe_num)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

void	exit_process(int status)
{
	if (status == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (status == EXIT_FAILURE_FILE)
	{
		perror("File open error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_FORK)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_MALLOC)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_PIPE)
	{
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
}
