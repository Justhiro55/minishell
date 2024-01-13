/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:20:47 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/13 20:34:47 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	type_quote(char a)
{
	if (a == '"' || a == '\'')
	{
		if (a == '"')
			return (CHAR_DQUOTE);
		if (a == '\'')
			return (CHAR_QUOTE);
	}
	return (0);
}

int	is_quote_end(int quote, t_tokeniser *tk, char *line)
{
	char	c;

	c = line[tk->str_i + tk->str_len];
	if (quote | CHAR_QUOTE && c == '\'')
	{
		return (1);
	}
	if (quote | CHAR_DQUOTE && c == '"')
	{
		return (1);
	}
	return (0);
}

void	cre_tokeniser(t_tokeniser *tk, char *line)
{
	char	c;

	tk->quoted = 0;
	while (line[tk->str_i + tk->str_len] != '\0')
	{
		c = line[tk->str_i + tk->str_len];
		if ((c == ' ' || c == '	') && !check_space(tk, line))
			break ;
		switch_quote_state(tk, c);
		if (check_meta_line(tk, line))
			break ;
		if ((c == '|' || c == '>' || c == '<'))
		{
			tk->quoted = REDIRECT;
			if (c == '|')
				tk->quoted = PIPE;
			tk->str_len += redi_size(tk, line);
			break ;
		}
		tk->str_len++;
	}
	tk->head_list = tokenadd_back(tk->head_list, ft_substr(line, tk->str_i,
				tk->str_len), tk->quoted);
	tk->str_i += tk->str_len;
	skip_space(tk, line);
}

void	clear_tokeniser(t_tokeniser *tk)
{
	free(tk->str);
	free(tk);
}

t_token	*lexer_main(char *line, t_tokeniser	*tokeniser, t_info *info)
{
	t_token		*token;

	tokeniser->str_i = 0;
	while (line[tokeniser->str_i] != '\0')
	{
		skip_space(tokeniser, line);
		tokeniser->str_len = 0;
		cre_tokeniser(tokeniser, line);
	}
	if (check_syntax(tokeniser->head_list, info) == ERROR)
		return (NULL);
	token = tokeniser->head_list;
	free(tokeniser);
	return (token);
}
	
	