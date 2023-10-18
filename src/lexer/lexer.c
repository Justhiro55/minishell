/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:20:47 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/17 18:57:15 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	is_metachar(int c)
{
	if (c == '|' || c == '&' || c =='(' || c == ')' || c == '<' || c == '>' || c == ' ')
		return (1);
	if (c == '\'')
		return (2);
	if (c == '\"')
		return (3);
	return (0);
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

int	type_quote(int c, t_tokeniser *tk)
{
	if (c == '"' || c == '\'')
	{
		tk->str_i++;
		if (c == '"')
			return (0x01);
		if (c == '\'')
			return (0x10);
	}
	return (0);
}

int	is_quote_end(int quote, int c)
{
	if (quote | CHAR_QUOTE && c == '\'')
		return (1);
	if (quote | CHAR_DQUOTE && c == '"')
		return (1);
	return (0);
}

void	cre_tokeniser(t_tokeniser *tk, char *line)
{
	char	c;
	size_t	i;
	int		quote;

	i = 0;
	quote = 0;
	while (line[tk->str_i + tk->str_len] != '\0')
	{
		c = line[tk->str_i + tk->str_len];
		if (quote == 0 && (c == '\'' || c == '"'))
			quote = type_quote(line[tk->str_i], tk);
		if (quote != 0 && is_quote_end(quote, line[tk->str_len]))
			break ;
		if (tk->str_len == 0 && (c == '|' || c == '>' || c == '<'))
		{
			tk->str_len += redi_size(tk, line);
			break ;
		}
		tk->str_len++;
	}
	// printf("");
	printf("str = [%zu]\ndiff str - i = [%zu]\n", tk->str_i, i - tk->str_i);
	tk->str_i += tk->str_i;
}

t_tokeniser	*init_tokeniser(void)
{
	t_tokeniser	*tokeniser;

	tokeniser = (t_tokeniser *)malloc(sizeof(t_tokeniser *));
	if (tokeniser == NULL)
		exit(1);
	ft_memset(tokeniser, 0, sizeof(t_tokeniser *));
	return (tokeniser);
}

t_token	*lexer_main(char *line)
{
	t_tokeniser	*tokeniser;
	// t_token		*token;
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
		// tokeniser->str_i++;
		i++;
		if (i == 10)
			break ;
	}
	return (NULL);
}

