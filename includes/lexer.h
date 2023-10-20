/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:50:57 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/20 19:52:41 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "./minishell.h"
# include "../func/libft/libft.h"
#include <stddef.h>

# define CHAR_QUOTE		0x01 // '
# define CHAR_DQUOTE	0x10 // "
# define PIPE			0x100 // |

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_tokeniser
{
	char		*str;
	int		str_i; //どこの配列から始まるのか
	int		str_len; //文字列の長さ
	int			quoted; //", ' を一つで管理する " = 0x01, ' = 0x10
	// t_token_state	state;
	t_token	*head_list;
}	t_tokeniser;


t_token	*lexer_main(char *line);
t_token	*tokenadd_back(t_token *head, char *str, int type);
t_token *tokenlast(t_token *lst);
t_token	*init_token(void);
t_tokeniser	*init_tokeniser(void);
void	printtoken(t_token *list);

void	skip_space(t_tokeniser *tk, char *line);
size_t	redi_size(t_tokeniser *tk, char *line);
int	check_space(int quote, t_tokeniser *tk, char *line);

#endif
