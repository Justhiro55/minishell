/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:56 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/25 14:37:13 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_env(char **token, t_info info)
{
	if (token[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR);
		return (ERROR);
	}
	if (token[1] == NULL)
	{
		if (info.env == NULL)
		{
			return (SUCCESS);
		}
		while (info.env != NULL)
		{
			if (info.env->value[0] != '\0')
				printf("%s=%s\n", info.env->key, info.env->value);
			info.env = info.env->next;
		}
	}
	return (SUCCESS);
}
