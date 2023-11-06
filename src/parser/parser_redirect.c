/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:13:00 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/03 16:31:03 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_redirect(t_now_token *ntk)
{
	char	*op;

	op = ft_strdup(ntk->now->str);
	if (ft_strncmp("<", op, ft_strlen(op)) == 0)
	{
	// printf("is redirect = [%s]\n", op);
	// printf("return = [%d]\n", REDIRECT_INPUT);
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

// t_redirects	*new_redirect(t_redirect_type *old_redi)
// {
// 	t_redirects	*new_redi;

// 	new_redi = ft_calloc(1, sizeof(t_redirects));
// 	old_redi->next = new_redi;
	
// }

t_node	*new_node_redirect(t_node *node, t_now_token *ntk)
{
	t_redirects	*redirect;

	printf("redirect\n");
	redirect = ft_calloc(1, sizeof(t_redirects));
	node->redirects = redirect;
	while (ntk->now != NULL && is_redirect(ntk))
	{
		redirect->type = is_redirect(ntk);
		ntk->now = ntk->now->next;
		redirect->filename = ft_strdup(ntk->now->str);
		ntk->now = ntk->now->next;
		if (ntk->now != NULL && is_redirect(ntk))
		{
			printf("continue\n");
			redirect->next = ft_calloc(1, sizeof(t_redirects));
			redirect = redirect->next;
		}
	}
	return	(node);
}