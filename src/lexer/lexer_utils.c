/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:07:34 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/23 17:28:27 by hhagiwar         ###   ########.fr       */
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

	if (quote & 0x01)
	c = line[tk->str_i + tk->str_len];
	if (quote & CHAR_DQUOTE && c == '"')
		return (1);
	if (quote & CHAR_QUOTE && c == '\'')
		return (1);
	return (0);
}
