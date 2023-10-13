/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/13 17:08:19 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

// void	ft_exec(t_info info, char **envp)
// {
// 	char	**path;
// 	int		i;
// 	t_env	*env;

// 	// char	*command_path;
// 	i = 0;
// 	env = info.env;
// 	while (ft_strcmp(env->key, "PATH") != 0)
// 		env = info.env->next;
// 	printf("env->key:%s\n", env->key);
// 	path = ft_split(info.env->value, ':');
// 	printf("path:%s\n", path[0]);
// 	while (access(ft_strjoin(path[i], info.token[0]), F_OK) != 0
// 		&& path[i] != NULL)
// 		i++;
// 	printf("access_ok_path:%s\n", ft_strjoin(path[i], info.token[0]));
// 	if (access(ft_strjoin(path[i], info.token[0]), F_OK) != 0)
// 		execve(ft_strjoin(path[i], info.token[0]), info.token, envp);
// }

void	set_token(t_info *info, char *line)
{
	info->token = ft_split(line, ' ');
}

int	ft_exec(t_info *info, char **envp)
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
		command_path = ft_strjoin(ft_strjoin(path[i], "/"), info->token[0]);
		if (access(command_path, F_OK) == 0)
		{
			execve(command_path, info->token, envp);
			return (0);
		}
		free(command_path);
		i++;
	}
	return (1);
}

void	parse(char *line, t_info *info, char **envp)
{
	int	status;

	set_token(info, line);
	pid_t pid = fork(); // プロセスをフォーク
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		// 子プロセス
		if (ft_strcmp(info->token[0], "exit") == 0)
			command_exit(info->token);
		else if (ft_strcmp(info->token[0], "echo") == 0)
			command_echo(info->token);
		else if (ft_strcmp(info->token[0], "pwd") == 0)
			command_pwd(info->token);
		else if (ft_strcmp(info->token[0], "cd") == 0)
			command_cd(info->token);
		else if (ft_strcmp(info->token[0], "env") == 0)
			command_env(info->token, *info);
		else if (ft_strcmp(info->token[0], "export") == 0)
			command_export(info->token, info);
		// else if (ft_strcmp(info->token[0], "ls") == 0)
		// 	command_ls(getcwd(NULL, 0));
		else if (ft_exec(info, envp) == 1)
		{
			command_not_found(line);
			exit(1); // 子プロセスを終了
		}
		exit(0); // 子プロセスを終了
	}
	else
	{
		// 親プロセス
		wait(&status); // 子プロセスの終了を待つ
		printf("status:%d\n", status);
	}
}
