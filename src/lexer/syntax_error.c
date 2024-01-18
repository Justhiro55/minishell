/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:08:11 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/18 20:27:37 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	output_syntax_error(int i)
{
	char	*error;

	(void)i;
	error = ft_strdup("syntax error\n");
	write(1, error, ft_strlen(error));
	free(error);
	exit(1);
}

int	check_rd(t_token *head, int *meta_flag, int *rd_flag, t_info *info)
{
	(void)head;
	if (*rd_flag > 0 || *meta_flag > 0)
		return (syntax_error(info));
	if (head->next == NULL)
		return (syntax_error(info));
	if (*rd_flag == 1 && (head->next == NULL || head->next->type & REDIRECT))
		return (syntax_error(info));
	*rd_flag = 1;
	return (SUCCESS);
}

int	check_meta(t_token *head, int *meta_flag, int *rd_flag, t_info *info)
{
	if (ft_strlen(head->str) > 1)
		return (syntax_error(info));
	if (head->prev == NULL)
		return (syntax_error(info));
	if (head->next == NULL)
		return (syntax_error(info));
	if (*meta_flag > 0 || *rd_flag > 0)
		return (syntax_error(info));
	*meta_flag = 1;
	*rd_flag = 0;
	return (SUCCESS);
}

void	check_eof(t_token *head, int meta_flag, int rd_flag, t_info *info)
{
	if (head->next == NULL)
	{
		if (meta_flag || rd_flag)
			syntax_error(info);
	}
}

int	check_syntax(t_token *token, t_info *info)
{
	t_token	*head;
	int		meta_flag;
	int		rd_flag;

	head = token;
	meta_flag = 0;
	rd_flag = 0;
	while (head != NULL)
	{
		if (head->type & PIPE
			&& check_meta(head, &meta_flag, &rd_flag, info) == ERROR)
			return (ERROR);
		else if (!(head->type & PIPE))
			meta_flag = 0;
		if (head->type & REDIRECT
			&& check_rd(head, &meta_flag, &rd_flag, info) == ERROR)
			return (ERROR);
		else if (!(head->type & REDIRECT))
			rd_flag = 0;
		head = head->next;
	}
	return (0);
}
