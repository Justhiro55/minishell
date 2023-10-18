/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:50:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/18 15:44:28 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

void	set_var(t_info *info, char **argv, int argc);
int		ft_exec(char **command, char **envp, t_info *info);
int		**get_pipe(t_info info);

void	child_process(int *pipefd, t_info info, char **envp, int i)
{
	pid_t	parent;

	parent = fork();
	if (!parent)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_exec(info.cmd[i], envp, &info);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(parent, NULL, 0);
	}
}

int	ft_pipe(char **envp, t_info info)
{
	pid_t	parent;
	int		**pipefd;
	int		i;

	pipefd = get_pipe(info);
	dup2(info.file_fd[0], STDIN_FILENO);
	i = 0;
	while (i < info.pipe_num - 1)
	{
		child_process(pipefd[i], info, envp, i);
		i++;
	}
	dup2(info.file_fd[1], STDOUT_FILENO);
	ft_exec(info.cmd[i], envp, &info);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	if (argc < 5)
	{
		fprintf(stderr, "Usage: %s <file1> <command1> <command2> <file2>\n",
				argv[0]);
		return (1);
	}
	set_env(&info, envp);
	set_var(&info, argv, argc);
	ft_pipe(envp, info);
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int	main(int argc, char *argv[]) {
//     if (argc < 2) {
//         printf("Usage: %s <command1> [<args>] | <command2> [<args>] | ...\n",
// 		argv[0]);
//         return (1);
//     }

//     int num_pipes = argc - 1;
//     int pipes[num_pipes - 1][2];

//     // Create pipes
//     for (int i = 0; i < num_pipes - 1; i++) {
//         if (pipe(pipes[i]) == -1) {
//             perror("Pipe creation failed");
//             return (1);
//         }
//     }

//     for (int i = 0; i < num_pipes; i++) {
//         pid_t pid = fork();
//         if (pid == -1) {
//             perror("Fork failed");
//             return (1);
//         }
//         if (pid == 0) {
//             // Child process
//             if (i > 0) {
//                 // Redirect input from the previous pipe
//                 dup2(pipes[i - 1][0], STDIN_FILENO);
//                 close(pipes[i - 1][0]);
//                 close(pipes[i - 1][1]);
//             }
//             if (i < num_pipes - 1) {
//                 // Redirect output to the next pipe
//                 dup2(pipes[i][1], STDOUT_FILENO);
//                 close(pipes[i][0]);
//                 close(pipes[i][1]);
//             }
//             execlp(argv[i + 1], argv[i + 1], NULL);
//             perror("Command execution failed");
//             exit(EXIT_FAILURE);
//         }
//     }
//     // Close all pipes in the parent process
//     for (int i = 0; i < num_pipes - 1; i++) {
//         close(pipes[i][0]);
//         close(pipes[i][1]);
//     }

//     // Wait for all child processes to finish
//     for (int i = 0; i < num_pipes; i++) {
//         wait(NULL);
//     }
//     return (0);
// }
