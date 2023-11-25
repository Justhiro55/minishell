/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:55:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/25 15:24:19 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	contains_non_numeric(const char *str)
{
	size_t	i;

	if (str == NULL || *str == '\0')
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	print_error_and_exit(char *str)
{
	ft_putstr_fd("exit: ", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	return (255);
}

int	command_exit(char **token, t_info *info, t_node *node)
{
	int	status;

	status = -1;
	ft_putstr_fd("exit\n", STDERR);
	if (token[1] == NULL)
		status = 0;
	else if (contains_non_numeric(token[1]) == 1)
		status = print_error_and_exit(token[1]);
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
