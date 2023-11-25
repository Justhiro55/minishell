/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:55:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/25 17:29:40 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	contains_non_numeric(const char *str)
{
	size_t	i;

	if (str == NULL || *str == '\0')
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	print_error_and_return(char *str)
{
	ft_putstr_fd("exit: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	return (255);
}

int	is_outside_long_range(char *str)
{
	int			negative;
	long long	value;

	if (str == NULL || ft_strlen(str) > 21)
		return (1);
	negative = 0;
	value = 0;
	if (*str == '-')
	{
		negative = 1;
		str++;
	}
	while (*str != '\0')
	{
		if ((negative && (-(value) < (LONG_MIN / 10) || (-(value) == LONG_MIN
						/ 10 && *str - '0' == 9))) || (!negative
				&& (value > LONG_MAX / 10 || (value == LONG_MAX / 10 && *str
						- '0' > LONG_MAX % 10))))
			return (1);
		value = value * 10 + (*str - '0');
		str++;
	}
	return (0);
}

int	command_exit(char **token, t_info *info, t_node *node)
{
	int	status;

	status = -1;
	ft_putstr_fd("exit\n", STDERR);
	if (token[1] == NULL)
		status = 0;
	else if (contains_non_numeric(token[1]) == 1
			|| is_outside_long_range(token[1]) == 1)
		status = print_error_and_return(token[1]);
	else if (token[2] == NULL)
	{
		if (ft_atoi(token[1]) < 0)
			status = 256 + (ft_atoi(token[1]) % 256);
		else
			status = ft_atoi(token[1]) % 256;
	}
	else
		ft_putstr_fd("exit: too many arguments\n", STDERR);
	if (status != -1)
	{
		free_node(node);
		free_info(info);
		exit(status);
	}
	return (ERROR);
}
