/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:58 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/12 18:05:53 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../func/libft/libft.h"
# include "./exec.h"
# include "./lexer.h"
# include "./minishell.h"
# include "./token.h"

typedef struct s_token	t_token;

typedef enum e_redirect_type
{
	REDIRECT_INPUT = 1,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND_OUTPUT,
	REDIRECT_HEREDOC,
}						t_redirect_type;

typedef enum e_nodetype
{
	NODE_COMMAND,
	NODE_PIPE,
}						t_nodetype;

typedef struct s_redirects
{
	t_redirect_type		type;
	int					fd;
	int					fd_file;
	int					fd_backup;
	char				*filename;
	struct s_redirects	*next;
}						t_redirects;

typedef struct s_node
{
	t_nodetype		type;
	char			**data;
	size_t			row_size;
	t_redirects		*redirects;
	struct s_node	*right;
	struct s_node	*left;
}					t_node;

t_node					*parser(t_token *token);
typedef struct s_now_token
{
	t_token				*now;
}						t_now_token;

//parser
t_node					*cmd(t_now_token *ntk);
t_redirects				*new_list_redirect(t_node *node, t_now_token *ntk);
size_t					count_word_rd(t_now_token *ntk);

//redirect
int						is_redirect(t_now_token *ntk);
t_node					*new_node_redirect(t_node *node, t_now_token *ntk);

//utils.
t_node					*new_node(char *str, t_node *left, t_node *right);
t_node					*new_node_cmd(t_now_token *ntk);
t_node					*new_node_cmdname(t_now_token *ntk);
void					printTree(t_node *root, size_t depth);
char					*create_text(char *text, size_t str_size);
char					*check_text(char *text);

#endif
