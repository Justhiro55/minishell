/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/07 15:21:36 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	set_token(t_info *info, char *line)
{
	info->token = ft_split(line, ' ');
}

void	parse(char *line, t_info info)
{

	set_token(&info, line);
	if (ft_strcmp(info.token[0], "exit") == 0)
		command_exit(info.token);
	else if (ft_strcmp(info.token[0], "echo") == 0)
		command_echo(info.token);
	else if (ft_strcmp(info.token[0], "pwd") == 0)
		command_pwd(info.token);
	else if (ft_strcmp(info.token[0], "cd") == 0)
		command_cd(info.token);
	else if (ft_strcmp(info.token[0], "env") == 0)
		command_env(info.token, info);
	else if (ft_strcmp(info.token[0], "export") == 0)
		command_export(info.token, info);
	else
		command_not_found(line);
	add_history(line);
	free(line);
}
