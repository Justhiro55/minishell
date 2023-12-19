/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/19 18:48:03 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	remove_quotes_in_place(char *str);

int	execute_from_path(char *command_name, char **tokens, char **envp,
		char **path)
{
	int		i;
	int		result;
	char	*command_path;

	result = -2;
	command_path = NULL;
	i = 0;
	while (path[i])
	{
		command_path = set_command_path(path[i], command_name);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
		{
			if (tokens[1] != NULL && tokens[1][0] != '\0')
				remove_quotes_in_place(tokens[1]);
			result = execute_command(command_path, tokens, envp);
			free(command_path);
			return (result);
		}
		free(command_path);
		i++;
	}
	return (result);
}
void	env_lstclear(t_env **lst);

int	execute_no_env(char **command, char **envp, t_node *node, t_info *info)
{
	char	*new_command;

	(void)node;
	if (info->env == NULL)
	{
		new_command = (char *)malloc(strlen("/bin/") + strlen(command[0]) + 1);
		if (new_command != NULL)
		{
			ft_strlcpy(new_command, "/bin/", ft_strlen("/bin/")
				+ ft_strlen(command[0]) + 1);
			ft_strlcat(new_command, command[0], ft_strlen("/bin/")
				+ ft_strlen(command[0]) + 1);
			free(command[0]);
			command[0] = new_command;
			if (access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
				return (execute_command(command[0], command, envp));
		}
	}
	return (command_not_found(command[0]));
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
		return (info->status % 255);
	if (command != NULL && command[0] != NULL && command[0][0] == '/'
		&& access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
		return (execute_command(command[0], command, envp));
	env = find_env_path(info);
	if (env)
		path = ft_split(env->value, ':');
	if (!env || !path)
		return (execute_no_env(command, envp, node, info));
	result = execute_from_path(command[0], command, envp, path);
	ft_free_array(path);
	if (result == -2)
	{
		result = 127;
		command_not_found(command[0]);
	}
	return (result);
}

int	ft_exec(char **command, char **envp, t_info *info, t_node *node)
{
	int	status;

	status = 0;
	if (command == NULL || command[0] == NULL || (int)command[0][0] == 0)
		return (1);
	if (command[0][0] == '/' || command[0][0] == '.')
	{
		if (access(command[0], F_OK) == 0 && access(command[0], X_OK) == 0)
		{
			if (command[1] != NULL && command[1][0] != '\0')
				remove_quotes_in_place(command[1]);
			return (execute_command(command[0], command, envp));
		}
		else
		{
			printf("No such file or directory\n");
			return (127);
		}
	}
	else
		status = execute_command_from_path(command, envp, info, node);
	return (status);
}
