/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:55:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/02 18:53:20 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_pwd(char **token)
{
	if (token[1] != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR);
		return (1);
	}
	else
	{
		ft_putstr_fd(getcwd(NULL, 0), STDOUT);
		ft_putstr_fd("\n", STDOUT);
	}
	return (0);
}
