/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:55:59 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/09 16:20:49 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # include "../func/get_next_line/get_next_line.h"
# include "../func/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# define STDOUT 1
# define STDERR 2
# define MINISHELL "MINISHELL$ "

# define ERROR 1

struct s_env;

typedef struct s_info
{
	char			**token;
	struct s_env	*env;
}					t_info;

typedef struct s_error
{
	int				**error;
}					t_error;

void				minishell(char **envp);
void				parse(char *line, t_info *info);

//signal
void				sig_int_input(int signum);
void				sig_quit_input(int signum);

#endif
