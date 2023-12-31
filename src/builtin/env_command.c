/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:56 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/26 10:08:44 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_env(char **token, t_info info)
{
	if (token[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", token[1]);
		return (ERROR);
	}
	while (info.env != NULL)
	{
		if (info.env->value[0] != '\0')
			printf("%s=%s\n", info.env->key, info.env->value);
		info.env = info.env->next;
	}
	return (SUCCESS);
}
