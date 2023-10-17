/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:50:57 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/17 16:56:16 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

#include "./minishell.h"
# include "../func/libft/libft.h"
#include <stddef.h>

// # define EXPANDABLE			0x01
// # define EXPANDABLE_QUOTED	0x02
// # define NON_EXPANDABLE		0x03
// # define PIPE				0x04
// // # define EXPANDABLE			0x05

// # define STR	0
// # define RDIR	1
// # define RRDIR	2
// # define LDIR	3
// # define LLDIR	4
// # define LLLDIR	5
// # define SPACE	6
// # define SQUOTE	7
// # define DQUOTE	8
// # define PIPE	9
// # define DPIPE	10
// # define AND	11
// # define DAND	12
// # define SCOLON	13
// # define DSCOLON	14
// # define DOLL	15
// # define ESC	16
// # define SSTR	17
// # define RINT	18

// typedef enum	e_tokentype{
// 	CHAR_GENERAL = -1,
// 	CHAR_PIPE = '|',
// 	CHAR_QOUTE = '\'',
// 	CHAR_DQUOTE = '\"',
// 	CHAR_SEMICOLON = ';',
// 	CHAR_WHITESPACE = ' ',
// 	CHAR_ESCAPE = '\\',
// 	CHAR_GREATER = '>',
// 	CHAR_LESSER = '<',
// 	CHAR_TAB = '\t',
// 	CHAR_NULL = 0,
// 	D_SEMICOLON = -4,
// 	D_GREATER = -3,
// 	IO_NUMBER = -2,
// 	TOKEN = -1,
// }				t_token_type;

typedef enum e_tokentype
{
	CHAR_GENERAL = -1,
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_PIPE = '|',
	CHAR_WHITESPACE = ' ',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_D_GREATER = -4,
	CHAR_D_LESSER,
	CHAR_IO_NUMBER,
}	t_tokentype;

# define CHAR_QUOTE		0x01
# define CHAR_DQUOTE	0x10


typedef struct s_tokeniser
{
	char		*str;
	size_t		str_i; //どこの配列から始まるのか
	size_t		str_len; //文字列の長さ
	int			quoted; //", ' を一つで管理する " = 0x01, ' = 0x10
	// t_token_state	state;
}	t_tokeniser;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*lexer_main(char *line);
void	tokenadd_back(t_token *list, t_token *new);
t_token *tokenlast(t_token *lst);
t_token	*init_token(void);
t_tokeniser	*init_tokeniser(void);

#endif
