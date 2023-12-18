/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:12:19 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/18 18:08:50 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		exit(1);
	ft_memset(token, 0, sizeof(t_token));
	return (token);
}

int	syntax_error(t_info *info)
{
	ft_putstr_fd(": syntax error near unexpected token `newline'\n", STDERR);
	info->status = 258;
	return (ERROR);
}
