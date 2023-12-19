/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:13:34 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/19 17:38:23 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int		is_variable(char **dst, char **rest, char *p, t_info *info);

int	append_double_quote(char **dst, char **rest, char *p, t_info *info)
{
	int	status;

	status = 0;
	if (*p == '\"')
	{
		append_char(dst, *((*rest)++));
		while (**rest && **rest != '\"')
		{
			if (**rest == '$')
			{
				status = is_variable(dst, rest, p, info);
				if (status == -1)
					return (-1);
				while (status != 1 && **rest != '\0' && **rest != '\"'
					&& **rest != ' ' && **rest != '$')
					(*rest)++;
			}
			else
				append_char(dst, *((*rest)++));
		}
		if (**rest == '\"')
			append_char(dst, *((*rest)++));
	}
	return (0);
}

void	append_single_quote(char **dst, char **rest, char *p)
{
	if (*p == '\'')
	{
		append_char(dst, *((*rest)++));
		while (**rest && **rest != '\'')
			append_char(dst, *((*rest)++));
		if (**rest == '\'')
			append_char(dst, *((*rest)++));
	}
}

int	expand_variable(t_node *node, t_info *info)
{
	int			i;
	t_redirects	*redirects;

	i = 0;
	redirects = node->redirects;
	if (node == NULL)
		return (0);
	while (node->data[i] != NULL)
		expand_variable_tok(&(node->data[i++]), info);
	while (redirects != NULL)
	{
		if (redirects != NULL && redirects->type != REDIRECT_HEREDOC)
			expand_variable_tok(&redirects->filename, info);
		redirects = redirects->next;
	}
	return (0);
}
