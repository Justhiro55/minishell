/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:26:02 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/07 17:50:28 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

void	error_signal(void)
{
	ft_putstr_fd(strerror(errno), STDERR);
	exit(EXIT_FAILURE);
}

void	change_signal(int flag)
{
	if (flag == 0)
	{
		if (signal(SIGINT, sigint_handler_nonl) == SIG_ERR)
			error_signal();
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			error_signal();
	}
	if (flag == 1)
	{
		if (signal(SIGINT, sigin_handler_heredoc) == SIG_ERR)
			error_signal();
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			error_signal();
	}
}
