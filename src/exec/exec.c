/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/28 15:23:20 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

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

int	search_and_execute_command(char *command_name, char **tokens, char **envp,
		char **path)
{
	int		i;
	int		result;
	char	*command_path;

	result = 1;
	command_path = NULL;
	i = 0;
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
	return (result);
}

int	execute_command_from_path(char **command, char **envp, t_info *info,
		t_node *node)
{
	char	**path;
	t_env	*env;
	int		result;

	path = NULL;
	env = NULL;
	result = 1;
	if (builtin_command(command, info, node) == 0)
		return (0);
	if (command != NULL && command[0] != NULL && command[0][0] == '/'
		&& access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
		return (execute_command(command[0], command, envp));
	env = find_env_path(info);
	if (env)
		path = ft_split(env->value, ':');
	if (!env || !path)
		return (ERROR);
	result = search_and_execute_command(command[0], command, envp, path);
	ft_free_array(path);
	if (result == 1)
		command_not_found(command[0]);
	return (result);
}

int	ft_exec(char **command, char **envp, t_info *info, t_node *node)
{
	if (command == NULL || command[0] == NULL)
		return (1);
	if (command[0][0] == '/')
	{
		if (access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
			return (execute_command(command[0], command, envp));
	}
	return (execute_command_from_path(command, envp, info, node));
}
