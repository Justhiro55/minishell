/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:50:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/13 16:13:47 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

char	*get_command_path(char *command)
{
	(void)command;
	printf("access:%d\n", access("/bin/cat", F_OK));
	while ()
		return (NULL);
	// if ((ft_strcmp(command, "cat") == 1) || (ft_strcmp(command, "echo") == 1)
	// 	|| (ft_strcmp(command, "ls") == 1) || ft_strcmp(command,
	// 		"norminette") == 1 || ft_strcmp(command, "mkdir") == 1
	// 	|| ft_strcmp(command, "bash") == 1 || ft_strcmp(command, "rm") == 1
	// 	|| ft_strcmp(command, "pwd") == 1)
	// 	return ("/bin/");
	// else if ((ft_strcmp(command, "man") == 1) || (ft_strcmp(command,
	// 			"env") == 1) || (ft_strcmp(command, "head") == 1)
	// 			|| (ft_strcmp(command, "wc") == 1) || (ft_strcmp(command,
	// 			"make") == 1) || (ft_strcmp(command, "whoami") == 1)
	// 		|| (ft_strcmp(command, "vim") == 1) || (ft_strcmp(command,
	// 				"cat") == 1) || (ft_strcmp(command, "cd") == 1)
	// 		|| (ft_strcmp(command, "env") == 1))
	// 	return ("/usr/bin/");
	return (NULL);
}

char	*ft_parse_args(char **command, char **envp, t_info *info)
{
	char	*command_path;

	if (ft_strcmp(command[0], "pwd") == 0)
		command_pwd(command);
	else if (ft_strcmp(command[0], "exit") == 0)
		command_exit(command);
	else if (ft_strcmp(command[0], "wc") == 0)
		execve("/usr/bin/wc", command, envp);
	else if (ft_strcmp(command[0], "pwd") == 0)
		command_pwd(command);
	else if (ft_strcmp(command[0], "export") == 0)
		command_export(command, info);
	else if (ft_strcmp(command[0], "ls") == 0)
	{
		printf("%s\n", getcwd(NULL, 0));
		command_ls(getcwd(NULL, 0));
	}
	command_path = ft_strjoin(get_command_path(command[0]), command[0]);
	printf("command_path:%s\n", command_path);
	execve(command_path, command, envp);
	return (NULL);
}

// char	*ft_parse_args(char **command, char **envp, t_info *info)
// {
// 	if (ft_strcmp(command[0], "cat") == 0)
// 		execve("/bin/cat", command, envp);
// 	else if (ft_strcmp(command[0], "head") == 0)
// 		execve("/usr/bin/head", command, envp);
// 	else if (ft_strcmp(command[0], "wc") == 0)
// 		execve("/usr/bin/wc", command, envp);
// 	else if (ft_strcmp(command[0], "ls") == 0)
// 		execve("/bin/ls", command, envp);
// 	else if (ft_strcmp(command[0], "pwd") == 0)
// 		command_pwd(command);
// 	else if (ft_strcmp(command[0], "exit") == 0)
// 		command_exit(command);
// 	else if (ft_strcmp(command[0], "echo") == 0)
// 		command_echo(command);
// 	else if (ft_strcmp(command[0], "pwd") == 0)
// 		command_pwd(command);
// 	else if (ft_strcmp(command[0], "cd") == 0)
// 		command_cd(command);
// 	else if (ft_strcmp(command[0], "env") == 0)
// 		execve("/usr/bin/env", command, envp);
// 	else if (ft_strcmp(command[0], "export") == 0)
// 		command_export(command, info);
// 	else if (ft_strcmp(command[0], "ls") == 0)
// 		command_ls(getcwd(NULL, 0));
// 	return (NULL);
// }

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_info	info;
	int		pipefd[2];
	char	**command1;
	char	**command2;
	char	*file[2];

	if (argc != 5)
	{
		fprintf(stderr, "Usage: %s <file1> <command1> <command2> <file2>\n",
				argv[0]);
		return (1);
	}
	set_env(&info, envp);
	file[0] = strdup(argv[1]);
	file[1] = strdup(argv[4]);
	command1 = ft_split(argv[2], ' ');
	command2 = ft_split(argv[3], ' ');
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	printf("test2\n");
	if (pid == 0)
	{
		close(pipefd[0]);
		printf("test3\n");
		dup2(pipefd[1], STDOUT_FILENO);
		printf("test4\n");
		close(pipefd[1]);
		// execve(ft_parse_args(command1), command1, envp);
		ft_parse_args(command1, envp, &info);
		// perror("execve");
		exit(1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	printf("test1\n");
	ft_parse_args(command2, envp, &info);
	// execve(ft_parse_args(command2), command2, envp);
	// perror("execve");
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
