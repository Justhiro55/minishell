/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:07:34 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/20 20:41:17 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tokeniser	*init_tokeniser(void)
{
	t_tokeniser	*tokeniser;

	tokeniser = (t_tokeniser *)malloc(sizeof(t_tokeniser *));
	if (tokeniser == NULL)
		exit(1);
	ft_memset(tokeniser, 0, sizeof(t_tokeniser *));
	tokeniser->head_list = init_token();
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

int	check_space(int quote, t_tokeniser *tk, char *line)
{
	char	c;

	printf("quote = [%d]\n", quote);
	if (quote & 0x01)
		printf("quote\n");
	c = line[tk->str_i + tk->str_len];
	if (quote & CHAR_DQUOTE && c == '"')
		return (1);
	if (quote & CHAR_QUOTE && c == '\'')
		return (1);
	return (0);
}
