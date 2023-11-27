/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:39 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/27 19:13:25 by kotainou         ###   ########.fr       */
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
			op = ft_strdup(ntk->now->str);
		else
			op = ft_strdup("");
		if (ft_strncmp("|", op, 1) == 0)
		{
			ntk->now = ntk->now->next;
			node = new_node(op, node, cmd(ntk));
		}
		else
			return (node);
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

void	clear_token(t_token *token)
{
	t_token	*now;
	t_token	*next;

	now = token;
	while (now != NULL)
	{
		next = now->next;
		free(now->str);
		free(now);
		now = next;
	}
}

t_node	*parser(t_token *token)
{
	t_now_token	*ntk;
	t_node		*node;

	ntk = ft_calloc(1, sizeof(t_now_token));
	ntk->now = token;
	node = expr(ntk);
	printtoken(token);
	clear_token(token);
	printf("node = [%s]\n", node->data[0]);
	// printTree(node, 0);
	// printf("node = [%s]\n", node->data[0]);
	return (node);
}
