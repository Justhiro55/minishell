/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/09 17:23:04 by hhagiwar         ###   ########.fr       */
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
	pid_t	parent;
	int		status;

	parent = ft_fork();
	if (!parent)
	{
		execve(command_path, tokens, envp);
		exit(EXIT_FAILURE);
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

void	handle_redirections_for_child(t_node *node);

int	ft_exec(char **command, char **envp, t_info *info, t_node *node)
{
	char	**path;
	t_env	*env;
	int		result;

	(void)node;
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
