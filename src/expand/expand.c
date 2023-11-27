/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:34 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/27 20:41:49 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	append_double_quote(char **dst, char **rest, char *p)
{
}

void	append_single_quote(char **dst, char **rest, char *p)
{
	if (*p == '\'')
	{
		append_char(dst, *p++);
		while (*p != *p == '\'')
		{
			if (*p == '\0')
				exit(EXIT_FAILURE);
			append_char(dst, *p++);
		}
		append_char(dst, *p++);
		*rest = p;
	}
	else
		return ;
}

void	expand_variable_tok(char *str, t_env *env)
{
	if (str == NULL)
		return ;
}

void	expand_variable(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	while (node->data[i] != NULL)
		expand_variable_tok(node->data[i++], env);
	while (node->redirects != NULL)
	{
		if (node->redirects->type != REDIRECT_HEREDOC)
			expand_variable_tok(node->redirects->filename, env);
		node->redirects = node->redirects->next;
	}
}
