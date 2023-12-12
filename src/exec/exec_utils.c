/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:29:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/12 17:59:14 by kotainou         ###   ########.fr       */
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
	else if (ft_strcmp(command[0], "unset") == 0)
		command_unset(command, info);
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
		exit(execve(command_path, tokens, envp));
	else
	{
		waitpid(parent, &status, 0);
		return (status != 0);
	}
}
