/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:36:39 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/30 19:06:31 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/minishell.h"
#include "../includes/sig.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		minishell(envp);
}

void	minishell(char **envp)
{
	char	*line;
	t_info	info;

	line = NULL;
	set_env(&info, envp);
	change_signal(0);
	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
		{
			free(line);
			signal_ctrl();
		}
		else if (line[0] == '\0')
			free(line);
		else
			parse(line, &info, envp);
		change_signal(0);
		check_signal(&info);
		g_signal = 0;
	}
}

// void	sig_int_input(int signum)
// {
// 	(void)signum;
// 	if (signum == SIGABRT)
// 		printf("test1\n");
// 	else if (signum == SIGQUIT)
// 		printf("test2\n");
// 	exit(0);
// 	// ft_putstr_fd("\b\b  \b\n", STDERR);
// 	// ft_putstr_fd(MINISHELL, STDERR);
// }

// void	sig_quit_input(int signum)
// {
// 	(void)signum;
// 	printf("test1\n");
// 	ft_putstr_fd("\b\b  \b\b", STDERR);
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q minishell");
// }
