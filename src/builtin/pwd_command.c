/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:55:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/14 21:32:14 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	command_pwd(char **token)
{
	char	*cwd;

	(void)token;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (ERROR);
	}
	ft_putstr_fd(cwd, STDOUT);
	ft_putstr_fd("\n", STDOUT);
	free(cwd);
	return (SUCCESS);
}
