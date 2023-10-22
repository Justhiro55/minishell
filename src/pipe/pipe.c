/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:50:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/22 13:28:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

void	set_var(t_info *info, char **argv, int argc);
int		ft_exec(char **command, char **envp, t_info *info);
int		**get_pipe(t_info info);
void	free_cmd(char ***cmd, int cmd_count);
void	free_fd(int **pipefd, int pipe_num);

#define EXIT_FAILURE_FILE 2
#define EXIT_FAILURE_PIPE 3
#define EXIT_FAILURE_FORK 4
#define EXIT_FAILURE_MALLOC 5

void	exit_process(int status)
{
	if (status == EXIT_SUCCESS)
		exit(EXIT_SUCCESS);
	else if (status == EXIT_FAILURE_FILE)
	{
		perror("File open error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_FORK)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_MALLOC)
	{
		perror("Malloc error");
		exit(EXIT_FAILURE);
	}
	else if (status == EXIT_FAILURE_PIPE)
	{
		perror("Pipe error");
		exit(EXIT_FAILURE);
	}
}

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

int	get_filefd(char *file, int type)
{
	int	fd;

	if (type == 0)
		fd = open(file, O_RDONLY);
	else if (type == 1)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
	{
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	here_doc(char *delimiter)
{
	char	*line;
	int		fd[2];
	pid_t	parent;

	line = NULL;
	if (pipe(fd) == -1)
		exit_process(EXIT_FAILURE_PIPE);
	if (parent < 0)
		exit_process(EXIT_FAILURE_FORK);
	if (!parent)
	{
		close(fd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		free(line);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(parent, NULL, 0);
	}
}

int	ft_pipe(char **envp, t_info info, int argc, char **argv)
{
	int	**pipefd;
	int	file_fd[2];
	int	i;

	set_var(&info, argv, argc);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		here_doc(argv[2]);
	else
	{
		file_fd[0] = get_filefd(argv[1], 0);
		dup2(file_fd[0], STDIN_FILENO);
	}
	file_fd[1] = get_filefd(argv[argc - 1], 1);
	pipefd = get_pipe(info);
	i = -1;
	while (i++ < info.pipe_num - 2)
		child_process(pipefd[i], info, envp, i);
	dup2(file_fd[1], STDOUT_FILENO);
	ft_exec(info.cmd[i], envp, &info);
	free_fd(pipefd, info.pipe_num);
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
	ft_pipe(envp, info, argc, argv);
	free_cmd(info.cmd, info.pipe_num);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }
