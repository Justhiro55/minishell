/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:07:34 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/12 17:38:25 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tokeniser	*init_tokeniser(void)
{
	t_tokeniser	*tokeniser;

	tokeniser = (t_tokeniser *)malloc(sizeof(t_tokeniser));
	if (tokeniser == NULL)
		exit(1);
	ft_memset(tokeniser, 0, sizeof(t_tokeniser));
	// tokeniser->head_list = init_token();
	return (tokeniser);
}

void	skip_space(t_tokeniser *tk, char *line)
{
	while (line[tk->str_i] == ' ')
	{
		tk->str_i++;
	}
}

size_t	redi_size(t_tokeniser *tk, char *line)
{
	char	c;

	c = line[tk->str_i];
	if (c == '<' || c == '>' || line[tk->str_i + 1])
	{
		if (line[tk->str_i] == line[tk->str_i + 1])
			return (2);
	}
	return (1);
}

int	check_space(t_tokeniser *tk, char *line)
{
	(void)line;
	if (tk->quoted)
		return (1);
	return (0);
}

void	switch_quote_state(t_tokeniser *lex, char c)
{
	if (lex->quoted == 0 && type_quote(c))
	{
		lex->quoted = type_quote(c);
		lex->quote_type = c;
	}
	else if (lex->quoted && c == lex->quote_type)
	{
		lex->quoted = 0;
		lex->quote_type = 0;
	}
}
