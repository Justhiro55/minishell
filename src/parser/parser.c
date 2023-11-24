/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:39 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/24 18:48:39 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_node	*expr(t_now_token *ntk)
{
	t_node	*node;
	char	*op;

	node = cmd(ntk);
	while (1)
	{
		if (ntk->now != NULL && ntk->now->str != NULL)
		{
			op = ft_strdup(ntk->now->str);
		}
		else
		{
			op = ft_strdup("");
		}
		if (ft_strncmp("|", op, 1) == 0)
		{
			ntk->now = ntk->now->next;
			node = new_node(op, node, cmd(ntk));
		}
		else
		{
			return (node);
		}
	}
	return (node);
}

t_node	*cmd(t_now_token *ntk)
{
	char	*cmd;
	

	cmd = ft_strdup(ntk->now->str);
	if (ntk->now->next != NULL && ft_strncmp(ntk->now->next->str, "|", 1) != 0)
	{
		return (new_node_cmdname(ntk));
	}
	return (new_node_cmd(ntk));
}

t_node	*parser(t_token	*token)
{
	t_now_token	*ntk;
	t_node		*node;

	ntk = ft_calloc(1, sizeof(t_now_token));
	ntk->now = token;
	node = expr(ntk);
	// printf("---print tree---\n");
	// printTree(node, 0);
	return (node);
}