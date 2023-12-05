/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:20:55 by kotainou          #+#    #+#             */
/*   Updated: 2023/12/05 18:21:30 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"

volatile sig_atomic_t	g_signal = 0;

void	signal_ctrl(void)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(0);
}

void	sigint_handler_in_process(int sig)
{
	(void) sig;
	printf("\n");
}

void	sigquit_handler_in_process(int sig)
{
	(void) sig;
	printf("Quit: %d\n", sig);
}

void	sigint_handler_nonl(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGQUIT)
		;
	g_signal = 1;
}

void	setup_signals(void)
{
	if (signal(SIGINT, sigint_handler_nonl) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(EXIT_FAILURE);
	}
}

void	exec(t_node *node, t_info *info)
{
	if (node == NULL)
		return ;
	if (node->type)
		;
	(void)info;
}

void	signals_exec_next(t_node *node, t_info *info)
{
	if (node == NULL)
	{
	}
	exec(node, info);
	setup_signals();
}

void	signals_exec(t_node *node, t_info *info)
{
	if (g_signal == 1)
	{
		g_signal = 0;
	}
	else if (g_signal == 130 || g_signal == 131)
	{
		g_signal = 0;
	}
	signals_exec_next(node, info);
}

void	exec_in_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_signal = 130;
	}
	else if (sig == SIGQUIT)
	{
		write(STDIN_FILENO, "Quit: 3\n", 9);
		g_signal = 131;
	}
}

void	setup_exec_signal(void)
{
	if (signal(SIGINT, exec_in_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, exec_in_signal) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR);
		exit(EXIT_FAILURE);
	}
}
