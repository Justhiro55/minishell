/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:03:44 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/06 18:38:46 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

t_env	*find_env_path(t_info *info)
{
	t_env	*env;

	env = info->env;
	while (env != NULL && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	return (env);
}

char	*set_command_path(char *path, char *command)
{
	char	*path_slash;
	char	*command_path;

	path_slash = ft_strjoin(path, "/");
	command_path = ft_strjoin(path_slash, command);
	free(path_slash);
	return (command_path);
}
