/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:34 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/27 18:43:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_alpha_under(char c)
{
	return ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) || c == '_');
}

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	append_double_quote(char **dst, char **rest, char *p)
{
}

void	append_single_quote(char **dst, char **rest, char *p)
{
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
		expand_variable_tok(node->data[i++]);
	while (node->redirects != NULL)
	{
		if (node->redirects->type != REDIRECT_HEREDOC)
			expand_variable_tok(node->redirects->filename);
		node->redirects = node->redirects->next;
	}
}
