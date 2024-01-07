/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:47:25 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/07 15:23:12 by kotainou         ###   ########.fr       */
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
		write (STDIN_FILENO, "\n", 1);
		g_signal = 130;
	}
	if (sig == SIGQUIT)
		g_signal = 131;
}
