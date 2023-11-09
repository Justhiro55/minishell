/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:27:39 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/09 17:08:15 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "minishell.h"


//pipe
# define EXIT_FAILURE_FILE 2
# define EXIT_FAILURE_PIPE 3
# define EXIT_FAILURE_FORK 4
# define EXIT_FAILURE_MALLOC 5
# define EXIT_FAILURE_DUP 6

// struct s_env;
// struct t_info;

//signal
void			sig_int_input(int signum);
void			sig_quit_input(int signum);

//pipe
void			free_cmd(char ***cmd, int cmd_count);
void			free_fd(int **pipefd, int pipe_num);
void			exit_process(int status);
void			free_fd(int **pipefd, int pipe_num);


#endif
