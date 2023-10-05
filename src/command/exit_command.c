/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:55:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/05 17:27:06 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int	command_exit(char **token)
{
	if (token[1] == NULL)
		exit(0);
	else if (token[2] == NULL)
		exit(atoi(token[1]));
	else
		ft_putstr_fd("exit: too many arguments\n", STDERR);
	return (1);
}
