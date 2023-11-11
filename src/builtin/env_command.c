/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:56 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/11 13:00:54 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_env(char **token, t_info info)
{
	if (token[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR);
		return (1);
	}
	if (token[1] == NULL)
	{
		if (info.env == NULL)
		{
			return (0);
		}
		while (info.env != NULL)
		{
			if (info.env->value[0] != '\0')
				printf("%s=%s\n", info.env->key, info.env->value);
			info.env = info.env->next;
		}
	}
	return (0);
}
