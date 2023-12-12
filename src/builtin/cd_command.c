/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:53:36 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/12 17:37:11 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_cd(char **token)
{
	if (token[1] == NULL || ft_strcmp(token[1], "~") == 0)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	if (token[2] != NULL)
		return (1);
	if (chdir(token[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR);
		ft_putstr_fd(token[1], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd("\n", STDERR);
	}
	return (0);
}
