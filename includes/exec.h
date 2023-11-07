/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:23:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/06 17:28:29 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

//pipe_def
# define EXIT_FAILURE_FILE 2
# define EXIT_FAILURE_PIPE 3
# define EXIT_FAILURE_FORK 4
# define EXIT_FAILURE_MALLOC 5

// struct s_env;
// struct t_info;

//signal
void				sig_int_input(int signum);
void				sig_quit_input(int signum);

//pipe
void				free_cmd(char ***cmd, int cmd_count);
void				free_fd(int **pipefd, int pipe_num);
void				exit_process(int status);
void				free_fd(int **pipefd, int pipe_num);

//builtin-command
int					command_exit(char **token);
int					command_not_found(char *line);
int					command_echo(char **token);
int					command_pwd(char **token);
int					command_cd(char **token);
int					command_env(char **token, t_info info);
t_env				*command_export(char **token, t_info *info);
void				command_ls(const char *dir_path);

//set
void				set_env(t_info *info, char **envp);
void				set_token(t_info *info, char *line);

//util
t_env				*env_lstlast(t_env *lst);
t_env				*env_lstnew(char *envp);
void				env_add_back(t_info *info, t_env *new_node);
void				ft_free_array(char **array);
t_env				*find_env_path(t_info *info);
char				*set_command_path(char *path, char *command);

///
void				execute_parent_process(t_info info, char **envp,
						t_node *node, int *fd);
void				child_process(t_info info, char **envp, t_node *node);
void				execute_child_process(t_info info, char **envp,
						t_node *node, int *fd);
void				set_node(t_node *node);
void				exit_process(int status);
int					ft_exec(char **command, char **envp, t_info *info);

#endif
