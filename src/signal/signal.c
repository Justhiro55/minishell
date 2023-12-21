/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:20:55 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/21 15:47:21 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sig.h"

volatile sig_atomic_t	g_signal = 0;

void	error_signal(void)
{
	ft_putstr_fd(strerror(errno), STDERR);
	exit(EXIT_FAILURE);
}

void	signal_ctrl(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}

void	sigint_handler_nonl(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		;
	g_signal = 1;
}

static void	sigin_handler_heredoc(int sig)
{
	(void)sig;
	close(0);
	g_signal = SIGINT;
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

// void	setup_signals(void)
// {
// 	if (signal(SIGINT, sigint_handler_nonl) == SIG_ERR)
// 	{
// 		ft_putstr_fd(strerror(errno), STDERR);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
// 	{
// 		ft_putstr_fd(strerror(errno), STDERR);
// 		exit(EXIT_FAILURE);
// 	}
// }
