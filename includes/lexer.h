/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:50:57 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/25 18:50:19 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


# include "./token.h"
# include "../func/libft/libft.h"
# include "./exec.h"
# include "./lexer.h"
# include "./minishell.h"
# include "./parser.h"
# include <stddef.h>

typedef struct s_token t_token; // 既存の宣言に合わせて型名を指定


typedef struct s_tokeniser
{
	char	*str;
	int		str_i;   //どこの配列から始まるのか
	int		str_len; //文字列の長さ
	int		quoted;  //", ' を一つで管理する " = 0x01, ' = 0x10
	char	quote_type;
	t_token	*head_list;
}	t_tokeniser;

t_token	*lexer_main(char *line);
t_token	*tokenadd_back(t_token *head, char *str, int type);
t_token	*tokenlast(t_token *lst);
t_token	*init_token(void);
t_tokeniser	*init_tokeniser(void);

void		printtoken(t_token *list);
int			type_quote(char a);

void		skip_space(t_tokeniser *tk, char *line);
size_t		redi_size(t_tokeniser *tk, char *line);
int			check_space(t_tokeniser *tk, char *line);
void		clear_list(t_token *token);
void		switch_quote_state(t_tokeniser *lex, char c);

void		check_syntax(t_token *token);

#endif
