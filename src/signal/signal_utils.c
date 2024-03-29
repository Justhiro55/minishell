/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:47:25 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/10 11:39:17 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	check_signal(t_info *info)
{
	if (g_signal == 1)
		info->status = 1;
	else if (g_signal == 130)
		info->status = 130;
	else if (g_signal == 131)
		info->status = 131;
	g_signal = 0;
}

void	sigint_handler_cat(int sig)
{
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		g_signal = 130;
	}
	if (sig == SIGQUIT)
	{
		write(STDIN_FILENO, "QUIT: 3\n", 9);
		g_signal = 131;
	}
}
