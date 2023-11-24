/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:08:11 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/24 14:49:45 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	output_syntax_error(void)
{
	char	*error;

	error = ft_strdup("syntax error\n");
	write(1, error, ft_strlen(error));
	exit(1);
}

void	check_rd(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	printf("type = [%d]\n", head->type);
	if (head->next != NULL)
		printf("next = [%d]\n", head->next->type);
	if (head->type | REDIRECT && head->next != NULL && head->next->type | PIPE)
		printf("   PIPE\n");
	if (head->type | REDIRECT && head->next != NULL && head->next->type | REDIRECT)
		printf("   REDIRECT\n");
}

void	check_meta(t_token *head)
{
	// if (head->next != NULL)
	// {
	// 	if (head->next->str[0] == '|')
	// 		printf("meta adsfa\n");
	// }
	// printf("head->str = [%s]\n", head->str);
	if (ft_strlen(head->str) > 1)
		output_syntax_error();
	if (head->prev == NULL)
		output_syntax_error();
}

void	check_syntax(t_token *token)
{
	t_token	*head;

	head = token;
	printf("redirect = [%d]\n", REDIRECT);
	printf("PIPT = [%d]\n", PIPE);
	while (head->next != NULL)
	{
		if (head->str[0] == '|')
		{
			check_meta(head);
		}
		if (head->type | REDIRECT)
		{
			check_rd(head);
		}
		head = head->next;
	}
}
