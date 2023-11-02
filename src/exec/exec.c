/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:44:15 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/02 18:53:20 by hhagiwar         ###   ########.fr       */
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
	// else if (ft_strcmp(info->token[0], "ls") == 0)
	// 	command_ls(getcwd(NULL, 0));
	else
		return (1);
	return (0);
}

int	ft_exec(char **command, char **envp, t_info *info)
{
	char	**path;
	int		i;
	t_env	*env;
	char	*command_path;

	i = 0;
	env = info->env;
	while (env != NULL && ft_strcmp(env->key, "PATH") != 0)
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
