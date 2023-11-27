/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:23:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/27 13:25:01 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "./exec.h"
# include "./lexer.h" // t_redirects 型が宣言されているヘッダーファイル
# include "./lexer.h"
# include "./minishell.h"
# include "./parser.h" // t_redirects 型が宣言されているヘッダーファイル
# include "./parser.h" // t_node 型が宣言されているヘッダーファイル
# include "./parser.h"
# include "./token.h"

typedef struct s_redirects	t_redirects;

typedef struct s_node		t_node;

typedef struct s_info
{
	char			**token;
	struct s_env	*env;
}					t_info;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

# define PIPE_READ 0
# define PIPE_WRITE 1

# define EXIT_FAILURE_FILE 2
# define EXIT_FAILURE_PIPE 3
# define EXIT_FAILURE_FORK 4
# define EXIT_FAILURE_MALLOC 5
# define EXIT_FAILURE_DUP 6

void						parse(char *line, t_info *info, char **envp);

int							ft_exec(char **command, char **envp, t_info *info,
								t_node *node);

//builtin-command
int							builtin_command(char **command, t_info *info,
								t_node *node);
int							command_exit(char **token, t_info *info,
								t_node *node);
int							command_not_found(char *line);
int							command_echo(char **token);
int							command_pwd(char **token);
int							command_cd(char **token);
int							command_env(char **token, t_info info);
t_env						*command_export(char **token, t_info *info);
void						command_ls(const char *dir_path);

//redirect
void						child_process(t_info info, char **envp,
								t_node *node);
;
void						execute_parent_process(t_info info, char **envp,
								t_node *node, int *fd);
void						execute_child_process(t_info info, char **envp,
								t_node *node, int *fd);
void						execute_process(t_info info, char **envp,
								t_node *node, int *fd);
void						here_doc_mock(char *delimiter);
void						restore_stdin_stdout(int stdin_backup,
								int stdout_backup);

//set
void						set_node(t_node *node);
void						set_env(t_info *info, char **envp);
void						set_token(t_info *info, char *line);

//env
t_env						*env_lstlast(t_env *lst);
t_env						*env_lstnew(char *envp);
void						env_add_back(t_info *info, t_env *new_node);

//free
void						free_cmd(char ***cmd, int cmd_count);
void						free_fd(int **pipefd, int pipe_num);
void						free_fd(int **pipefd, int pipe_num);

//util
int							execute_command(char *command_path, char **tokens,
								char **envp);
void						exit_process(int status);
void						ft_free_array(char **array);
t_env						*find_env_path(t_info *info);
char						*set_command_path(char *path, char *command);
int							open_file(t_redirects *redirects);
int							ft_dup(int fd);
void						ft_dup2(int old_fd, int new_fd);
void						ft_pipe(int fd[2]);
pid_t						ft_fork(void);
void						here_doc_fork(t_redirects *redirects);

#endif
