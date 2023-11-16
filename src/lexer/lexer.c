/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:20:47 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/16 13:25:47 by kotainou         ###   ########.fr       */
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
	// int		quote;

	tk->quoted = 0;
	while (line[tk->str_i + tk->str_len] != '\0')
	{
		c = line[tk->str_i + tk->str_len];
		if (c == ' ' && !check_space(tk, line))
			break ;
		switch_quote_state(tk, c);
		if (tk->str_len == 0 && (c == '|' || c == '>' || c == '<'))
		{
			tk->quoted = REDIRECT;
			if (c == '|')
				tk->quoted = PIPE; 
			tk->str_len += redi_size(tk, line);
			break ;
		}
		tk->str_len++;
	}
	// printf("substr = [%s]\n", ft_substr(line, tk->str_i,tk->str_len));
	tk->head_list = tokenadd_back(tk->head_list, ft_substr(line, tk->str_i,
				tk->str_len), tk->quoted);
	tk->str_i += tk->str_len;
}

t_token	*lexer_main(char *line)
{
	t_tokeniser	*tokeniser;
	size_t		i;
	int			flag;

	(void)line;
	i = 0;
	flag = 0;
	tokeniser = init_tokeniser();
	tokeniser->str_i = 0;
	while (line[tokeniser->str_i] != '\0')
	{
		skip_space(tokeniser, line);
		tokeniser->str_len = 0;
		cre_tokeniser(tokeniser, line);
		// i++;
		// if (i == 10)
		// 	break ;
	}
	// printtoken(tokeniser->head_list);
	// check_syntax(tokeniser->head_list);
	return (tokeniser->head_list);
}
