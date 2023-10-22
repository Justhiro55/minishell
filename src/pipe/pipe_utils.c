/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:54:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/22 14:47:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

void	set_var(t_info *info, char **argv, int argc)
{
	int	i;
	int	here_doc;

	i = 0;
	here_doc = 0;
	if (ft_strcmp(argv[1], "here_doc") != 0)
		info->pipe_num = argc - 3;
	else
	{
		here_doc = 1;
		info->pipe_num = argc - 4;
	}
	info->cmd = (char ***)malloc(sizeof(char **) * info->pipe_num);
	if (info->cmd == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < info->pipe_num)
	{
		info->cmd[i] = ft_split(argv[i + 2 + here_doc], ' ');
		i++;
	}
}

int	**get_pipe(t_info info)
{
	int	**fd;
	int	i;

	i = 0;
	fd = (int **)malloc(sizeof(int *) * info.pipe_num);
	if (fd == NULL)
		exit(EXIT_FAILURE);
	while (i < info.pipe_num)
	{
		fd[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
	i = 0;
	while (i < info.pipe_num)
	{
		if (pipe(fd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (fd);
}

char	*get_path(t_info *info, char **command)
{
	char	**path;
	t_env	*env;
	int		i;
	char	*command_path;

	env = info->env;
	while (ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	path = ft_split(env->value, ':');
	i = 0;
	while (path[i] != NULL)
	{
		command_path = ft_strjoin(ft_strjoin(path[i], "/"), command[0]);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);
		i++;
	}
	return (NULL);
}

int	ft_exec(char **command, char **envp, t_info *info)
{
	char	*command_path;
	int		i;

	i = 0;
	command_path = get_path(info, command);
	if (command_path == NULL)
	{
		perror("command");
		exit(EXIT_FAILURE);
	}
	execve(command_path, command, envp);
	free(command_path);
	return (1);
}
