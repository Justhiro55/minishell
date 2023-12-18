/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:32:06 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/18 18:57:46 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	process_single_quote(char **new_word, char **p)
{
	append_single_quote(new_word, p, *p);
}

void	process_double_quote(char **new_word, char **p, t_info *info)
{
	append_double_quote(new_word, p, *p, info);
}

void	process_variable(char **new_word, char **p, t_info *info)
{
	is_variable(new_word, p, *p, info);
	while (**p != '\0' && **p != '\"' && **p != '$' && **p != '\'')
		(*p)++;
}

void	expand_variable_tok(char **str, t_info *info)
{
	char	*new_word;
	char	*p;

	if (*str == NULL)
		return ;
	p = *str;
	new_word = ft_calloc(1, sizeof(char));
	if (new_word == NULL)
		exit_process(EXIT_FAILURE_MALLOC);
	while (*p)
	{
		if (*p == '\'')
			process_single_quote(&new_word, &p);
		else if (*p == '\"')
			process_double_quote(&new_word, &p, info);
		else if (*p == '$')
			process_variable(&new_word, &p, info);
		else
			append_char(&new_word, *p++);
	}
	free(*str);
	*str = new_word;
}
