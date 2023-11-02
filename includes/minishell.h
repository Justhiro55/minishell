/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:55:59 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/02 19:16:11 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../func/libft/libft.h"
# include "./lexer.h"
# include "lexer.h"
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

# define STDOUT 1
# define STDERR 2
# define MINISHELL "MINISHELL$ "

# define ERROR 1

//pipe
# define EXIT_FAILURE_FILE 2
# define EXIT_FAILURE_PIPE 3
# define EXIT_FAILURE_FORK 4
# define EXIT_FAILURE_MALLOC 5

struct s_env;

typedef struct s_info
{
	char			**token;
	struct s_env	*env;
	//pipe
	int				pipe_num;
	int				file_fd[2];
	int				*pipe_fd;
	char			***cmd;
}					t_info;

# include "exec.h"

typedef struct s_error
{
	int				**error;
}					t_error;

void				minishell(char **envp);
void				parse(char *line, t_info *info, char **envp);

//signal
void				sig_int_input(int signum);
void				sig_quit_input(int signum);

void				exit_process(int status);
int					**get_pipe(t_info info);

#endif
