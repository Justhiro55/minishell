/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:12:59 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/16 15:48:14 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "./exec.h"
# include "./lexer.h"
# include "./minishell.h"
# include "./parser.h"
# include "./token.h"

# define CHAR_QUOTE		0x0001 // '
# define CHAR_DQUOTE	0x0010 // "
# define REDIRECT		0x0100 // < > << >>
# define PIPE			0x1000 // |

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif
