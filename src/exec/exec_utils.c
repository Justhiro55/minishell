/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:29:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/19 15:51:12 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	builtin_command(char **command, t_info *info, t_node *node)
{
	if (ft_strcmp(command[0], "exit") == 0)
		info->status = command_exit(command, info, node) % 255;
	else if (ft_strcmp(command[0], "echo") == 0)
		info->status = command_echo(command) % 255;
	else if (ft_strcmp(command[0], "pwd") == 0)
		info->status = command_pwd(command) % 255;
	else if (ft_strcmp(command[0], "cd") == 0)
		info->status = command_cd(command, info) % 255;
	else if (ft_strcmp(command[0], "env") == 0)
		info->status = command_env(command, *info) % 255;
	else if (ft_strcmp(command[0], "export") == 0)
		info->status = command_export(command, info) % 255;
	else if (ft_strcmp(command[0], "unset") == 0)
		info->status = command_unset(command, info) % 255;
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
