/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:15:57 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/24 14:49:54 by hhagiwar         ###   ########.fr       */
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

	new = token_new(str, type);
	if (head->str == NULL)
		return (new);
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
		free(token->str);
		free(p);
		p = next;
	}
	free(p);
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		exit(1);
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}
