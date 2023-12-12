/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:23:50 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/12 17:48:52 by kotainou         ###   ########.fr       */
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
