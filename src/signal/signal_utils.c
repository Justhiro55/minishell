/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:47:25 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/18 14:59:51 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	check_signal(t_info *info)
{
	if (g_signal == SIGINT)
		info->status = 1;
	else if (g_signal == 130)
		info->status = 130;
	else if (g_signal == 131)
		info->status = 131;
	g_signal = 0;
}
