/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:08:11 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/20 11:18:32 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	output_syntax_error(int i)
{
	char	*error;

	(void)i;
	error = ft_strdup("syntax error\n");
	// printf("[%d]\n", i);
	write(1, error, ft_strlen(error));
	exit(1);
}

void	check_rd(t_token *head, int rd_flag)
{
	t_token	*tmp;

	tmp = head;
	// printf("rd type = [%d]\n", head->type);
	// if (head->next != NULL)
	// 	printf("next = [%d]\n", head->next->type);
	// if (head->type | REDIRECT && head->next != NULL && head->next->type | PIPE)
	// 	printf("   PIPE\n");
	// if (head->type | REDIRECT && head->next != NULL && head->next->type | REDIRECT)
	// 	printf("   REDIRECT\n");
	// printf("rd = [%d] meta = [%d]\n", rd_flag, meta_flag);s
	if (rd_flag > 0)
		output_syntax_error(1);
}

void	check_meta(t_token *head, int meta_flag, int rd_flag)
{
	// if (head->next != NULL)
	// {
	// 	if (head->next->str[0] == '|')
	// 		printf("meta adsfa\n");
	// }
	// printf("head->str = [%s]\n", head->str);
	if (ft_strlen(head->str) > 1)
		output_syntax_error(2);
	if (head->prev == NULL)
		output_syntax_error(3);
	if (meta_flag > 0 || rd_flag > 0)
		output_syntax_error(4);
}

void	check_eof(t_token *head, int meta_flag, int rd_flag)
{
	if (head->next == NULL)
	{
		if (meta_flag || rd_flag)
			output_syntax_error(5);
	}
}

void	check_syntax(t_token *token)
{
	t_token	*head;
	int		meta_flag;
	int		rd_flag;

	head = token;
	meta_flag = 0;
	rd_flag = 0;
	while (head->next != NULL)
	{
		if (head->type & PIPE)
		{
			check_meta(head, meta_flag, rd_flag);
			meta_flag = 1;
			rd_flag = 0;
		}
		if (head->type & REDIRECT)
		{
			check_rd(head, rd_flag);
			meta_flag = 0;
			rd_flag = 1;
		}
		else
		{
			meta_flag = 0;
			rd_flag = 0;
		}
		// printf("while rd_flag = [%d] meta_flag = [%d]\n", rd_flag, meta_flag);
		head = head->next;
	}
	
}