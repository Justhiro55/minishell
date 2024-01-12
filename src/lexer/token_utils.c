/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:12:19 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/12 17:26:46 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		exit(1);
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}

int	syntax_error(t_info *info)
{
	ft_putstr_fd(": syntax error near unexpected token `newline'\n", STDERR);
	info->status = 258;
	return (ERROR);
}

int	check_meta_line(t_tokeniser *tk, char *line)
{
	char	next_c;
	char	now_c;

	next_c = '\0';
	now_c = line[tk->str_len + tk->str_i];
	if (line[tk->str_len + tk->str_i + 1] != '\0')
		next_c = line[tk->str_len + tk->str_i + 1];
	if (next_c == '|' || next_c == '>' || next_c == '<')
	{
		if (now_c == next_c)
		{
			tk->str_len += 2;
			return (1);
		}
		tk->str_len++;
		return (1);
	}
	return (0);
}
