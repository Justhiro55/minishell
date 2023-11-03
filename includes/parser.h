/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:58 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/03 13:23:10 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H


// # include "../func/libft/libft.h"
# include "./minishell.h"
// # include "./lexer.h"
# include <stddef.h>

typedef enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND_OUTPUT,
	REDIRECT_HEREDOC,
}	t_redirect_type;

typedef enum e_nodetype
{
	NODE_COMMAND,
	NODE_PIPE,
}	t_nodetype;

typedef struct s_redirects
{
	t_redirect_type		type;
	int					fd;
	int					fd_file;
	int					fd_backup;
	char				*filename;
	struct s_redirects	*next;
}	t_redirects;


typedef struct s_node
{
	t_nodetype		type;
	char			**data;
	size_t			row_size;
	t_redirects		*redirects;
	struct s_node	*right;
	struct s_node	*left;
}					t_node;

typedef	struct s_now_token
{
	t_token	*now;
}	t_now_token;

t_node	*parser(t_token	*token);

//parser
t_node	*cmd(t_now_token *ntk);

//redirect
int	is_redirect(t_now_token *ntk);
t_node	*new_node_redirect(t_node *node, t_now_token *ntk);

#endif
