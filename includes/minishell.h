/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:55:59 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/01/07 14:40:54 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../func/libft/libft.h"
# include "./exec.h"
# include "./lexer.h"
# include "./token.h"
# include "./sig.h"
# include "exec.h"
# include "lexer.h"
// # include "leakdetect.h"
# include "parser.h"
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

# include "../func/libft/libft.h"
# include "./exec.h"
# include "./lexer.h"
# include "./token.h"

// typedef struct s_info
// {
// 	char			**token;
// 	struct s_env	*env;
// }					t_info;

extern volatile sig_atomic_t		g_signal;

# define STDOUT 1
# define STDERR 2
# define MINISHELL "MINISHELL$ "

# define SUCCESS 0
# define ERROR 1

# define EXIT_FAILURE_FILE 2
# define EXIT_FAILURE_PIPE 3
# define EXIT_FAILURE_FORK 4
# define EXIT_FAILURE_MALLOC 5

void	minishell(char **envp);

//signal
void	sig_int_input(int signum);
void	sig_quit_input(int signum);

void	exit_process(int status);

void	setup_signals(void);

#endif
