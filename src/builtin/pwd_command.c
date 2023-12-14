/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:55:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/14 19:50:59 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_pwd(char **token)
{
	(void)token;
	ft_putstr_fd(getcwd(NULL, 0), STDOUT);
	ft_putstr_fd("\n", STDOUT);
	return (SUCCESS);
}
