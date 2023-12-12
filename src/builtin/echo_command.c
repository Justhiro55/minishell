/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:29 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/12 17:37:16 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	remove_quotes_in_place(char *str);

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

int	is_metacharacter(char c)
{
	return (c && ft_strchr("|&;()<> \t\n", c));
}

int	check_arg(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != NULL)
	{
		while (str[i][j] != '\0')
		{
			if (is_metacharacter(str[i][j]))
			{
				ft_putstr_fd("syntax error near unexpected token \'", STDOUT);
				ft_putchar_fd(str[i][j], STDOUT);
				ft_putstr_fd("\'\n", STDOUT);
				return (ERROR);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (SUCCESS);
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
	if (check_arg(token) == ERROR)
		return (ERROR);
	n_set = n_option(token);
	i = n_set;
	while (token[i])
	{
		remove_quotes_in_place(token[i]);
		ft_putstr_fd(token[i], STDOUT);
		if (token[i + 1])
			ft_putstr_fd(" ", STDOUT);
		i++;
	}
	if (n_set == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}
