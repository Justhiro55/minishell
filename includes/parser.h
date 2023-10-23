/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:58 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/23 17:47:15 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../func/libft/libft.h"
# include "./minishell.h"

typedef struct s_node
{
	t_nodetype		type;
	char			**data;
	t_redirects		*redirects;
	struct s_node	*right;
	struct s_node	*left;
}					t_node;

#endif
