/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:23:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/06 16:02:14 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "./minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;


//builtin-command
int					command_exit(char **token);
int					command_not_found(char *line);
int					command_echo(char **token);
int					command_pwd(char **token);
int					command_cd(char **token);
int					command_env(char **token, t_info info);

//set
void	set_env(t_info *info, char **envp);


#endif
