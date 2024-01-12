/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:50:57 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/10 15:39:36 by kotainou         ###   ########.fr       */
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
# include "./token.h"
# include <stddef.h>

typedef struct s_token	t_token;
typedef struct s_info	t_info;

typedef struct s_tokeniser
{
	char				*str;
	int					str_i;
	int					str_len;
	int					quoted;
	char				quote_type;
	t_token				*head_list;
}						t_tokeniser;

t_token					*lexer_main(char *line, t_tokeniser	*tokeniser,
							t_info *info);
t_token					*tokenadd_back(t_token *head, char *str, int type);
t_token					*tokenlast(t_token *lst);
t_token					*init_token(void);
t_tokeniser				*init_tokeniser(void);

void					printtoken(t_token *list);
int						type_quote(char a);

void					skip_space(t_tokeniser *tk, char *line);
size_t					redi_size(t_tokeniser *tk, char *line);
int						check_space(t_tokeniser *tk, char *line);
void					clear_list(t_token *token);
void					switch_quote_state(t_tokeniser *lex, char c);

int						check_syntax(t_token *token, t_info *info);
void					clear_tokeniser(t_tokeniser *tk);

//token_utils.c
t_token					*init_token(void);
int						syntax_error(t_info *info);
int						check_meta_line(t_tokeniser *tk, char *line);

#endif
