/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:15:57 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/02 19:57:15 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*token_last(t_token *token)
{
	t_token	*p;

	p = token;
	while (p != NULL && p->next != NULL)
	{
		p = p->next;
	}
	return (p);
}

t_token	*token_new(char *str, int type)
{
	t_token	*newnode;

	newnode = (t_token *)malloc(sizeof(t_token));
	if (newnode == NULL)
		return (NULL);
	newnode->str = str;
	newnode->type = type;
	newnode->next = NULL;
	newnode->prev = NULL;
	return (newnode);
}

t_token	*tokenadd_back(t_token *head, char *str, int type)
{
	t_token	*new;
	t_token	*last;

	if (head == NULL || head->str == NULL)
		return (token_new(str, type));
	new = token_new(str, type);
	last = token_last(head);
	new->prev = last;
	last->next = new;
	return (head);
}

void	printtoken(t_token *token)
{
	t_token	*p;

	p = token;
	printf("\n--print token--\n");
	while (p != NULL)
	{
		printf("str = [%s]\n", p->str);
		printf("type = [%d]\n", p->type);
		p = p->next;
	}
	printf("\n");
}

void	clear_list(t_token *token)
{
	t_token	*p;
	t_token	*next;

	p = token;
	while (p != NULL)
	{
		next = p->next;
		free(p->str);
		free(p);
		p = next;
	}
}
