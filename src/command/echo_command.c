/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:29 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/05 15:47:01 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_echo(char **token)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (token[1] == NULL)
	{
		ft_putstr_fd("\n", STDOUT);
		return (0);
	}
	if (ft_strcmp(token[1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (token[i])
	{
		ft_putstr_fd(token[i], STDOUT);
		if (token[i + 1])
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (n_flag != 1)
		ft_putstr_fd("\n", 1);
	return (0);
}
