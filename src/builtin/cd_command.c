/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:53:36 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/14 21:23:00 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_cd(char **token, t_info *info)
{
	if (token[1] == NULL || ft_strcmp(token[1], "~") == 0)
	{
		if (info->env == NULL)
		{
			printf("bash: cd: HOME not set\n");
			return (ERROR);
		}
		else
			chdir(getenv("HOME"));
		return (SUCCESS);
	}
	if (chdir(token[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR);
		ft_putstr_fd(token[1], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd("\n", STDERR);
	}
	return (SUCCESS);
}
