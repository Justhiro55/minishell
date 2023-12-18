/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:23:50 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/18 14:13:48 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_node	*new_node(char *str, t_node *left, t_node *right)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(1, sizeof(char *));
	node->data[0] = ft_strdup(str);
	node->data[1] = NULL;
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

int	is_redirect_token(char *op)
{
	int		type;

	type = 0;
	if (ft_strncmp("<", op, ft_strlen(op)) == 0)
		type = REDIRECT_INPUT;
	else if (ft_strncmp(">", op, ft_strlen(op)) == 0)
		type = REDIRECT_OUTPUT;
	else if (ft_strncmp("<<", op, ft_strlen(op)) == 0)
		type = REDIRECT_HEREDOC;
	else if (ft_strncmp(">>", op, ft_strlen(op)) == 0)
		type = REDIRECT_APPEND_OUTPUT;
	return (type);
}

t_token	*token_next(t_token *token, size_t *count)
{
	*count = *count + 1;
	return (token->next);
}

size_t	count_word(t_now_token *ntk)
{
	t_token	*token;
	size_t	count;
	size_t	i;

	token = ntk->now;
	count = 0;
	while (token != NULL && ft_strncmp(token->str, "|", 1) != 0
		&& is_redirect_token(token->str) == 0)
		token = token_next(token, &count);
	i = 0;
	if (token != NULL && is_redirect_token(token->str))
	{
		while (token != NULL && i < 2)
		{
			token = token->next;
			i++;
		}
	}
	while (token != NULL && ft_strncmp(token->str, "|", 1) != 0
		&& is_redirect_token(token->str) == 0)
		token = token_next(token, &count);
	if (count == 0)
		count++;
	return (count);
}
