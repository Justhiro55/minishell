/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:23:50 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/04 20:44:34 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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

	node = ft_calloc(2, sizeof(t_node));
	node->data = (char **)ft_calloc(2, sizeof(char *));
	node->data[0] = ft_strdup(ntk->now->str);
	node->data[1] = NULL;
	node->row_size = 1;
	ntk->now = ntk->now->next;
	return (node);
}

int	is_redirect_token(t_token *ntk)
{
	char	*op;

	op = ft_strdup(ntk->str);
	if (ft_strncmp("<", op, ft_strlen(op)) == 0)
		return (REDIRECT_INPUT);
	else if (ft_strncmp(">", op, ft_strlen(op)) == 0)
		return (REDIRECT_OUTPUT);
	else if (ft_strncmp("<<", op, ft_strlen(op)) == 0)
		return (REDIRECT_HEREDOC);
	else if (ft_strncmp(">>", op, ft_strlen(op)) == 0)
		return (REDIRECT_APPEND_OUTPUT);
	return (0);
}

size_t	count_word(t_now_token *ntk)
{
	t_token	*token;
	size_t	count;

	token = ntk->now;
	count = 0;
	while (token->next != NULL && ft_strncmp(token->next->str, "|", 1) != 0
		&& is_redirect_token(token) == 0)
	{
		count++;
		token = token->next;
	}
	if (count == 0)
		count++;
	return (count);
}

char	*check_text(char *text);

t_node	*new_node_cmdname(t_now_token *ntk)
{
	t_node	*node;
	char	*cmd;
	size_t	i;

	i = 0;
	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(count_word(ntk) + 1, sizeof(char *));
	while (ntk->now != NULL && ft_strncmp(ntk->now->str, "|", 1) != 0)
	{
		if (is_redirect(ntk))
			return (new_node_redirect(node, ntk));
		cmd = ft_strdup(ntk->now->str);
		check_text(cmd);
		node->data[i] = ft_strdup(cmd);
		// if (cmd != NULL)
		// 	free(cmd);
		i++;
		node->data[i] = NULL;
		ntk->now = ntk->now->next;
	}
	node->row_size = i;
	return (node);
}
