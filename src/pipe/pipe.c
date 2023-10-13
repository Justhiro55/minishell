/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:50:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/13 22:27:00 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

int	ft_exec(char **command, char **envp, t_info *info)
{
	char	**path;
	int		i;
	t_env	*env;
	char	*command_path;

	i = 0;
	env = info->env;
	while (ft_strcmp(env->key, "PATH") != 0 && i++ < 20)
		env = env->next;
	path = ft_split(env->value, ':');
	i = 0;
	while (path[i] != NULL)
	{
		command_path = ft_strjoin(ft_strjoin(path[i], "/"), command[0]);
		if (access(command_path, F_OK) == 0)
		{
			execve(command_path, command, envp);
			return (0);
		}
		free(command_path);
		i++;
	}
	return (1);
}

void	set_var(t_info *info, char **argv)
{
	info->cmd1 = ft_split(argv[2], ' ');
	info->cmd2 = ft_split(argv[3], ' ');
	info->file_fd[0] = open(argv[1], O_RDONLY);
	info->file_fd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->file_fd[0] < 0 || info->file_fd[1] < 0)
		exit(EXIT_FAILURE);
}

void	child_process(int fd1, int fd2, t_info info, char **envp)
{
	close(fd1);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	ft_exec(info.cmd1, envp, &info);
}

void	parent_process(int *fd, t_info info, char **envp)
{
	int	status;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	wait(&status); // 子プロセスの終了を待つ
	ft_exec(info.cmd2, envp, &info);
}

int	ft_pipe(char **argv, char **envp, t_info info)
{
	pid_t	parent;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	parent = fork();
	if (!parent)
	{
		child_process(pipefd[0], pipefd[1], info, envp);
		exit(1);
	}
	parent_process(pipefd, info, envp);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_info	info;

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s <file1> <command1> <command2> <file2>\n",
				argv[0]);
		return (1);
	}
	set_env(&info, envp);
	set_var(&info, argv);
	ft_pipe(argv, envp, info);
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
