/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/24 13:45:46 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	builtin_command(char **command, t_info *info, t_node *node)
{
	if (ft_strcmp(command[0], "exit") == 0)
		command_exit(command, info, node);
	else if (ft_strcmp(command[0], "echo") == 0)
		command_echo(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		command_pwd(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		command_cd(command);
	else if (ft_strcmp(command[0], "env") == 0)
		command_env(command, *info);
	else if (ft_strcmp(command[0], "export") == 0)
		command_export(command, info);
	else
		return (1);
	return (0);
}

int	execute_command(char *command_path, char **tokens, char **envp)
{
	pid_t	parent;
	int		status;

	parent = ft_fork();
	if (!parent)
	{
		exit(execve(command_path, tokens, envp));
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

int	ft_exec(char **command, char **envp, t_info *info, t_node *node)
{
	char	**path;
	t_env	*env;
	int		result;
	int		i;
	char	*command_path;

	path = NULL;
	env = NULL;
	result = 1;
	if (builtin_command(command, info, node) == 0)
		return (0);
	env = find_env_path(info);
	if (!env)
		return (1);
	path = ft_split(env->value, ':');
	i = 0;
	if (command != NULL && command[0] != NULL && command[0][0] == '/'
		&& access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
		return (execute_command(command[0], command, envp));
	while (path[i])
	{
		command_path = set_command_path(path[i], command[0]);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
		{
			result = execute_command(command_path, command, envp);
			free(command_path);
			ft_free_array(path);
			return (result);
		}
		free(command_path);
		i++;
	}
	command_not_found(command[0]);
	ft_free_array(path);
	return (ERROR);
}
