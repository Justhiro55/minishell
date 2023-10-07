/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:36:39 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/07 23:07:44 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	// while (*envp)
	// {
	// 	else
	// 		printf("%s\n", *envp);
	// 	envp++;
	// }
	if (argc == 1)
		minishell(envp);
}

// void	set_env(t_info *info, char **envp)
// {
// 	t_info	info;
// 	char	**key;
// 	char	**value;
// }

void	minishell(char **envp)
{
	char	*line;
	t_info	info;

	line = NULL;
	set_env(&info, envp);
	while (1)
	{
		line = readline("$> ");
		if (line == NULL || strlen(line) == 0)
			free(line);
		else
			parse(line, &info);
		// if (signal(SIGINT, sig_int_input) == SIG_ERR)
		// {
		// 	ft_putstr_fd(strerror(errno), STDERR);
		// 	exit(1);
		// }
		// if (signal(SIGQUIT, sig_quit_input) == SIG_ERR)
		// {
		// 	ft_putstr_fd(strerror(errno), STDERR);
		// 	exit(1);
		// }
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
