/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_found_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:56:32 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/05 15:44:43 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_not_found(char *line)
{
	if (line[0] != 10)
	{
		ft_putstr_fd("command not found: ", STDERR);
		ft_putstr_fd(line, STDERR);
	}
	ft_putstr_fd("\n", STDERR);
	return (1);
}
