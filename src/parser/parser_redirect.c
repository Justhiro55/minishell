/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:13:00 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/03 13:34:09 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_redirect(t_now_token *ntk)
{
	char	*op;

	op = ft_strdup(ntk->now->str);
	if (ft_strncmp("<", op, ft_strlen(op)) == 0)
	{
		return (REDIRECT_INPUT);
	}
	else if (ft_strncmp(">", op, ft_strlen(op)) == 0)
	{
		return (REDIRECT_OUTPUT);
	}
	else if (ft_strncmp("<<", op, ft_strlen(op)) == 0)
	{
		return (REDIRECT_APPEND_OUTPUT);
	}
	else if (ft_strncmp(">>", op, ft_strlen(op)) == 0)
	{
		return (REDIRECT_HEREDOC);
	}
	return (0);
}

t_node	*new_node_redirect(t_node *node, t_now_token *ntk)
{
	printf("redirect\n");
	while (ntk->now != NULL && is_redirect(ntk))
	{
		node->redirects->type = is_redirect(ntk);
		ntk->now = ntk->now->next;
		node->redirects->filename = ft_strdup(ntk->now->str);
		ntk->now = ntk->now->next;
	}
	return	(node);
}