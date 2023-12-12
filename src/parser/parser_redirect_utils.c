/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:50 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/12 18:00:42 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_redirects	*new_list_redirect(t_node *node, t_now_token *ntk)
{
	t_redirects	*redirect;

	redirect = ft_calloc(1, sizeof(t_redirects));
	redirect->fd_backup = ft_dup(STDIN_FILENO);
	node->redirects = redirect;
	redirect->type = is_redirect(ntk);
	ntk->now = ntk->now->next;
	redirect->filename = ft_strdup(ntk->now->str);
	ntk->now = ntk->now->next;
	redirect->next = NULL;
	return (redirect);
}

size_t	count_word_rd(t_now_token *ntk)
{
	t_token	*token;
	size_t	count;

	count = 0;
	token = ntk->now;
	while (token->next != NULL && ntk->now->str[0] == '-')
	{
		count++;
		token = token->next;
	}
	if (count == 0)
		count = 1;
	return (count);
}
