/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:15:57 by kotainou          #+#    #+#             */
/*   Updated: 2023/10/17 15:35:10 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

// t_tokeniser	*init_tokeniser(void)
// {
// 	t_tokeniser	*tokeniser;

// 	tokeniser = (t_tokeniser *)malloc(sizeof(t_tokeniser *));
// 	if (tokeniser == NULL)
// 		exit(1);
// 	ft_memset(tokeniser, 0, sizeof(t_tokeniser *));
// 	return (tokeniser);
// }

t_token	*init_token(void)
{
	t_token		*rnt_token;

	rnt_token = (t_token *)malloc(sizeof(t_token *));
	if (rnt_token == NULL)
		exit(1);
	ft_memset(rnt_token, 0, sizeof(t_token *));
	return (rnt_token);
}

t_token *tokenlast(t_token *lst)
{
	t_token	*p;

	if (lst->next == lst)
		return (lst);
	p = lst;
	while (p != NULL)
	{
		if (p == NULL)
			break ;
		p = p->next;
	}
	return (p);
}

void	tokenadd_back(t_token *list, t_token *new)
{
	t_token *p;

	if (new == NULL)
		return ;
	while (list == NULL)
	{
		list = new;
		return ;
	}
	p = tokenlast(list);
	new->next = NULL;
	new->prev = p;
	p->next = new;
}

void	tokenprint(t_token *list)
{
	t_token	*p;

	p = list;
	while (p != NULL)
	{
		printf("data = [%s]\n", p->str);
		p = p->next;
	}
}