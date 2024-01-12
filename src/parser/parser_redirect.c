/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:13:00 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/12 17:35:00 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_redirect(t_now_token *ntk)
{
	int		type;

	type = 0;
	if (ft_strncmp("<", ntk->now->str, ft_strlen(ntk->now->str)) == 0)
	{
		type = REDIRECT_INPUT;
	}
	else if (ft_strncmp(">", ntk->now->str, ft_strlen(ntk->now->str)) == 0)
	{
		type = REDIRECT_OUTPUT;
	}
	else if (ft_strncmp("<<", ntk->now->str, ft_strlen(ntk->now->str)) == 0)
	{
		type = REDIRECT_HEREDOC;
	}
	else if (ft_strncmp(">>", ntk->now->str, ft_strlen(ntk->now->str)) == 0)
	{
		type = REDIRECT_APPEND_OUTPUT;
	}
	return (type);
}

t_node	*redirect_add_cmd(t_now_token *ntk, t_node *node)
{
	size_t	i;

	i = 0;
	if (ntk->now != NULL && node->data[0] == NULL
		&& ft_strncmp("|", ntk->now->str, 1) != 0)
	{
		node->data[i] = ft_strdup(ntk->now->str);
		ntk->now = ntk->now->next;
		node->data[i + 1] = NULL;
		i++;
	}
	while (node->data[i] != NULL)
		i++;
	while (ntk->now != NULL && ft_strncmp("|", ntk->now->str, 1) != 0
		&& is_redirect(ntk) == 0)
	{
		node->data[i] = ft_strdup(ntk->now->str);
		ntk->now = ntk->now->next;
		node->data[i + 1] = NULL;
		i++;
	}
	return (node);
}

t_redirects	*last_list(t_redirects *redirect)
{
	t_redirects	*rd;

	rd = redirect;
	while (rd != NULL)
	{
		if (rd->next == NULL)
			break ;
		rd = rd->next;
	}
	return (rd);
}

t_redirects	*add_redirect(int type, char *filename, t_redirects *redirect)
{
	t_redirects	*add_rd;
	t_redirects	*last;

	add_rd = ft_calloc(1, sizeof(t_redirects));
	last = last_list(redirect);
	last->next = add_rd;
	add_rd->next = NULL;
	add_rd->filename = filename;
	add_rd->type = type;
	return (add_rd);
}

t_node	*new_node_redirect(t_node *node, t_now_token *ntk)
{
	t_redirects	*redirect;
	char		*filename;
	int			type;
	int			rd_count;

	rd_count = 0;
	redirect = new_list_redirect(node, ntk, &rd_count);
	while (ntk->now != NULL && ft_strncmp(ntk->now->str, "|", 1) != 0
		&& rd_count > 1)
	{
		if (!is_redirect(ntk))
			redirect_add_cmd(ntk, node);
		if (ntk->now == NULL || ft_strncmp(ntk->now->str, "|", 1) == 0)
			break ;
		type = is_redirect(ntk);
		ntk->now = ntk->now->next;
		filename = ft_strdup(ntk->now->str);
		ntk->now = ntk->now->next;
		add_redirect(type, filename, redirect);
	}
	redirect_add_cmd(ntk, node);
	return (node);
}
