/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:34 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/28 15:34:14 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int		is_variable(char **dst, char **rest, char *p, t_env *env);

void	append_double_quote(char **dst, char **rest, char *p, t_env *env)
{
	if (*p == '\"')
	{
		(*rest)++;
		while (**rest && **rest != '\"')
		{
			if (**rest == '$')
				is_variable(dst, rest, p, env);
			else
				append_char(dst, *((*rest)++));
		}
		if (**rest == '\"')
			(*rest)++;
	}
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

void	expand_variable_tok(char **str, t_env *env)
{
	char	*new_word;
	char	*p;

	(void)env;
	if (*str == NULL)
		return ;
	p = *str;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		exit_process(EXIT_FAILURE_MALLOC);
	while (*p && !is_metacharacter(*p))
	{
		if (*p == '\'')
			append_single_quote(&new_word, &p, p);
		else if (*p == '$')
		{
			is_variable(&new_word, &p, p, env);
			p += ft_strlen(new_word);
		}
		else
			append_char(&new_word, *p++);
	}
	free(*str);
	*str = new_word;
}

void	expand_variable(t_node *node, t_env *env)
{
	int			i;
	t_redirects	*redirects;

	i = 0;
	redirects = node->redirects;
	if (node == NULL)
		return ;
	while (node->data[i] != NULL)
		expand_variable_tok(&(node->data[i++]), env);
	while (redirects != NULL)
	{
		if (redirects != NULL && redirects->type != REDIRECT_HEREDOC)
			expand_variable_tok(&redirects->filename, env);
		redirects = redirects->next;
	}
	redirects = node->redirects;
}
