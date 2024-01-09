/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:29:25 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/01/09 17:10:44 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	remove_quotes(char *str);

int	builtin_command(char **command, t_info *info, t_node *node)
{
	if (ft_strcmp(command[0], "exit") == 0)
		info->status = command_exit(command, info, node);
	else if (ft_strcmp(command[0], "echo") == 0)
		info->status = command_echo(command);
	else if (ft_strcmp(command[0], "pwd") == 0)
		info->status = command_pwd(command);
	else if (ft_strcmp(command[0], "cd") == 0)
		info->status = command_cd(command, info);
	else if (ft_strcmp(command[0], "env") == 0)
		info->status = command_env(command, *info);
	else if (ft_strcmp(command[0], "export") == 0)
		info->status = command_export(command, info);
	else if (ft_strcmp(command[0], "unset") == 0)
		info->status = command_unset(command, info);
	else
		return (1);
	return (0);
}

int	execute_command(char *command_path, char **tokens, char **envp)
{
	pid_t	parent;
	int		status;
	int		i;

	i = 0;
	parent = ft_fork();
	if (!parent)
	{
		change_signal(0);
		exit(execve(command_path, tokens, envp));
	}
	else
	{
		change_signal(2);
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (ERROR);
	}
}

int	is_directory(char *command_path)
{
	struct stat	s;

	if (stat(command_path, &s) == 0 && (command_path[0] == '/'
			|| command_path[0] == '.'))
	{
		if (S_ISDIR(s.st_mode))
		{
			printf("%s: is a directory\n", command_path);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	check_permission(char *command_path)
{
	struct stat	s;

	if (stat(command_path, &s) == 0)
	{
		if ((s.st_mode & S_IRUSR) == 0)
		{
			printf(" Permission denied\n");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	restore_fd(int stdin_backup, int stdout_backup)
{
	int	status;

	status = 0;
	if (ft_dup2(stdout_backup, STDOUT_FILENO) == 1)
		status = 1;
	if (ft_dup2(stdin_backup, STDIN_FILENO) == 1)
		status = 1;
	close(stdout_backup);
	close(stdin_backup);
	return (status);
}
