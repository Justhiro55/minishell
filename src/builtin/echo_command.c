/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:29 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/11 12:55:43 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	n_option(char **token)
{
	int	i;
	int	j;

	i = 1;
	j = 2;
	while (token[i] && token[i][0] == '-' && token[i][1] == 'n')
	{
		j = 2;
		while (token[i][j] == 'n')
			j++;
		if (token[i][j] != '\0')
			break ;
		i++;
	}
	return (i);
}

int	command_echo(char **token)
{
	int	i;
	int	n_set;

	if (token[1] == NULL)
	{
		ft_putstr_fd("\n", STDOUT);
		return (0);
	}
	n_set = n_option(token);
	i = n_set;
	while (token[i])
	{
		ft_putstr_fd(token[i], STDOUT);
		if (token[i + 1])
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (n_set == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}
