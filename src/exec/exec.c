/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/07 11:24:11 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	set_token(t_info *info, char *line)
{
	info->token = ft_split(line, ' ');
}

int	builtin_command(t_info *info)
{
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
	else
		return (1);
	return (0);
}

int	execute_command(char *command_path, char **tokens, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		execve(command_path, tokens, envp);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else
	{
		wait(&status);
		return (0);
	}
}

int	execute_from_path(char **path, char *command_name, char **tokens,
		char **envp)
{
	int		i;
	char	*command_path;
	int		result;

	i = 0;
	result = 1;
	while (path[i])
	{
		command_path = set_command_path(path[i], command_name);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
		{
			result = execute_command(command_path, tokens, envp);
			free(command_path);
			return (result);
		}
		free(command_path);
		i++;
	}
	command_not_found(command_name);
	return (result);
}

int	ft_exec(char **command, char **envp, t_info *info)
{
	char	**path;
	t_env	*env;
	int		result;

	if (builtin_command(info) == 0)
		return (0);
	env = find_env_path(info);
	if (!env)
		return (1);
	path = ft_split(env->value, ':');
	result = execute_from_path(path, command[0], command, envp);
	ft_free_array(path);
	return (result);
}

// int	ft_exec(char **command, char **envp, t_info *info)
// {
// 	char	**path;
// 	int		i;
// 	t_env	*env;
// 	char	*command_path;

// 	i = 0;
// 	env = info->env;
// 	while (ft_strcmp(env->key, "PATH") != 0 && i++ < 20)
// 		env = env->next;
// 	path = ft_split(env->value, ':');
// 	i = 0;
// 	while (path[i] != NULL)
// 	{
// 		command_path = ft_strjoin(ft_strjoin(path[i], "/"), command[0]);
// 		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
// 		{
// 			execve(command_path, command, envp);
// 			return (0);
// 		}
// 		free(command_path);
// 		i++;
// 	}
// 	return (1);
// }

// void	parse(char *line, t_info *info, char **envp)
// {
// 	set_token(info, line);
// 	if (ft_exec(info, envp) == 1)
// 		command_not_found(line);
// }
