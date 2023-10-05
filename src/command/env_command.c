/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:54:56 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/05 15:46:59 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	command_env(char **token, char **envp)
{
	(void)envp;
	if (token[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR);
		return (1);
	}
	return (0);
}
