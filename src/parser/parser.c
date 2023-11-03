/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:10:39 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/03 13:42:01 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_node	*cmd(t_now_token *ntk);


t_node	*new_node(char *str, t_node *left, t_node *right)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(1, sizeof(char *));
	node->data[0] = ft_strdup(str);
	node->left = left;
	node->right = right;
	node->row_size = 1;
	node->type = NODE_PIPE;
	return (node);
}

t_node	*new_node_cmd(t_now_token *ntk)
{
	t_node	*node;

	// printf("new node cmd = [%s]\n", str);
	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(1, sizeof(char *));
	node->data[0] = ft_strdup(ntk->now->str);
	node->row_size = 1;
	ntk->now = ntk->now->next;
	return (node);
}

//
t_node	*new_node_cmdname(t_now_token *ntk)
{
	t_node	*node;
	size_t	i;

	i = 0;
	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(1, sizeof(char *));
	while (ntk->now != NULL && ft_strncmp(ntk->now->str, "|", 1) != 0)
	{
		if (is_redirect(ntk))
		{
			printf("no\n");
			return (new_node_redirect(node, ntk));
		}
		node->data[i] = ft_strdup(ntk->now->str);
		i++;
		ntk->now = ntk->now->next;
	}
	node->row_size = i;
	return (node);
}

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
	// printf("cmd = [%s]\n", cmd);
	if (ntk->now->next != NULL && ft_strncmp(ntk->now->next->str, "|", 1) != 0)
	{
		return (new_node_cmdname(ntk));
	}
	return (new_node_cmd(ntk));
}

void	printTree(t_node *root, size_t depth)
{
	size_t	i;

	if (root == NULL)
		return ;
	printTree(root->right, depth + 1);
	for (i = 0; i < depth; i++)
	{
		printf(" ");
	}
	// printf("redirect [%d] ", root->redirects->type);
	for (i = 0; i < root->row_size; i++)
	{
		if (i == 0)
			printf("+");
		if (i == 0 && root->type == NODE_PIPE)
			printf("type PIPE ");
		else if(i == 0 && root->type == NODE_COMMAND)
			printf("type COMMAND ");
		printf("%s ", root->data[i]);
	}
	printf("\n");
	printTree(root->left, depth + 1);
	depth++;
}

t_node	*parser(t_token	*token)
{
	t_now_token	*ntk;
	t_node		*node;

	ntk = ft_calloc(1, sizeof(t_now_token));
	ntk->now = token;
	node = expr(ntk);
	printTree(node, 0);
	return (node);
}