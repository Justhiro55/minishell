/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 17:20:47 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/17 17:36:35 by kotainou         ###   ########.fr       */
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

void	cre_tokeniser(t_tokeniser *tk, char *line)
{
	char	c;
	size_t	str_len;

	str_len = 0;
	while (line[tk->str_i + str_len] != '\0')
	{
		c = line[tk->str_i + str_len];
		if (tk->str_i == 0 && (c == '|' || c == '>' || c == '<'))
		{
			tk->str_i += setting_size(tk, line);
			break ;
		}
		if (tk->quoted | CHAR_QUOTE)
	}
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
		cre_tokeniser(tokeniser, line);
	}
	return (NULL);
}

