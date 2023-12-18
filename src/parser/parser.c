/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:39 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/18 18:04:19 by kotainou         ###   ########.fr       */
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
		{
			free(op);
			return (node);
		}
		free(op);
	}
	return (node);
}

t_node	*cmd(t_now_token *ntk)
{
	if (ntk->now->next != NULL && ft_strncmp(ntk->now->next->str, "|", 1) != 0)
	{
		return (new_node_cmdname(ntk));
	}
	return (new_node_cmd(ntk));
}

void	free_ntk(t_now_token *ntk)
{
	free(ntk->now);
	free(ntk);
}

t_node	*parser(t_token *token, t_info *info)
{
	t_now_token	*ntk;
	t_node		*node;

	ntk = ft_calloc(1, sizeof(t_now_token));
	if (ntk == NULL)
		return (NULL);
	ntk->now = token;
	node = expr(ntk);
	free(ntk);
	clear_list(token);
	return (node);
}
