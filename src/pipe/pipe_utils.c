/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 22:54:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/18 18:15:54 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

void	set_var(t_info *info, char **argv, int argc)
{
	int	i;

	i = 0;
	info->file_fd[0] = open(argv[1], O_RDONLY);
	info->file_fd[1] = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->file_fd[0] < 0 || info->file_fd[1] < 0)
	{
		perror("File open error");
		exit(EXIT_FAILURE);
	}
	info->pipe_num = argc - 3;
	info->cmd = (char ***)malloc(sizeof(char **) * info->pipe_num);
	if (info->cmd == NULL)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	while (i < info->pipe_num)
	{
		info->cmd[i] = ft_split(argv[i + 2], ' ');
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
		fd[i] = (int *)malloc(sizeof(int) * info.pipe_num);
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

int	ft_exec(char **command, char **envp, t_info *info)
{
	char	**path;
	int		i;
	t_env	*env;
	char	*command_path;

	i = 0;
	env = info->env;
	while (ft_strcmp(env->key, "PATH") != 0 && i++ < 20)
		env = env->next;
	path = ft_split(env->value, ':');
	i = 0;
	while (path[i] != NULL)
	{
		command_path = ft_strjoin(ft_strjoin(path[i], "/"), command[0]);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
		{
			execve(command_path, command, envp);
			return (0);
		}
		free(command_path);
		i++;
	}
	return (1);
}

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
