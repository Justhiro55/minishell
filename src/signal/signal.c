/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:48:18 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/27 18:58:55 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sig.h" 

# include <readline/readline.h>
# include <readline/history.h>
# include <readline/readline.h>


// void	sigint_handler_in_process(int sig)
// {
// 	(void) sig;
// 	printf("\n");
// }

// void	sigquit_handler_in_process(int sig)
// {
// 	(void) sig;
// 	printf("Quit: %d\n", sig);
// }

void	sigint_handler_nonl(int sig)
{
	rl_on_new_line();
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

// void	sigint_handler(int sig)
// {
// 	printf("\n");
// 	rl_on_new_line();
// 	// rl_replace_line("", 0);
// 	rl_redisplay();
// 	(void) sig;
// }

void	setup_signals(void)
{
	if (signal(SIGINT, sigint_handler_nonl) == SIG_ERR)
		exit(EXIT_FAILURE);
// 	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
// 		exit(EXIT_FAILURE);
}

