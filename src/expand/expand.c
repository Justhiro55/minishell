/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:34 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/01 19:43:33 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int		is_variable(char **dst, char **rest, char *p, t_info *info);

int	append_double_quote(char **dst, char **rest, char *p, t_info *info)
{
	if (*p == '\"')
	{
		(*rest)++;
		while (**rest && **rest != '\"')
		{
			if (**rest == '$')
			{
				if (is_variable(dst, rest, p, info) == -1)
					return (-1);
			}
			else
				append_char(dst, *((*rest)++));
		}
		if (**rest == '\"')
			(*rest)++;
	}
	return (0);
}

void	append_single_quote(char **dst, char **rest, char *p)
{
	if (*p == '\'')
	{
		(*rest)++;
		while (**rest && **rest != '\'')
			append_char(dst, *((*rest)++));
		if (**rest == '\'')
			(*rest)++;
	}
}

void	expand_variable_tok(char **str, t_info *info)
{
	char	*new_word;
	char	*p;

	if (*str == NULL)
		return ;
	p = *str;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		exit_process(EXIT_FAILURE_MALLOC);
	while (*p && !is_metacharacter(*p))
	{
		if (*p == '\'')
		{
			append_single_quote(&new_word, &p, p);
			p += ft_strlen(p);
		}
		if (*p == '\"')
		{
			append_double_quote(&new_word, &p, p, info);
			p += ft_strlen(p);
		}
		else if (*p == '$')
		{
			is_variable(&new_word, &p, p, info);
			while (*p != '\0' && *p != '\"' && *p != '$')
				p++;
			// p += ft_strlen(new_word);
		}
		else
			append_char(&new_word, *p++);
	}
	free(*str);
	*str = new_word;
}

void	expand_variable(t_node *node, t_info *info)
{
	int			i;
	t_redirects	*redirects;

	i = 0;
	redirects = node->redirects;
	if (node == NULL)
		return ;
	while (node->data[i] != NULL)
		expand_variable_tok(&(node->data[i++]), info);
	while (redirects != NULL)
	{
		if (redirects != NULL && redirects->type != REDIRECT_HEREDOC)
			expand_variable_tok(&redirects->filename, info);
		redirects = redirects->next;
	}
}
