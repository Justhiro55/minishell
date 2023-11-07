/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:58 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/07 17:28:43 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../func/libft/libft.h"
# include "./minishell.h"

typedef enum e_nodetype
{
	NODE_COMMAND,
	NODE_PIPE,
}						t_nodetype;

typedef enum e_redirect_type
{
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	REDIRECT_APPEND_OUTPUT,
	REDIRECT_HEREDOC,
}						t_redirect_type;

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
	t_nodetype			type;
	char				**data;
	t_redirects			*redirects;
	struct s_node		*right;
	struct s_node		*left;
}						t_node;
#endif
