/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:50:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/18 18:38:56 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

void	set_var(t_info *info, char **argv, int argc);
int		ft_exec(char **command, char **envp, t_info *info);
int		**get_pipe(t_info info);
void	free_cmd(char ***cmd, int cmd_count);
void	free_fd(int **pipefd, int pipe_num);

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
	set_var(&info, argv, argc);
	ft_pipe(envp, info);
	free_cmd(info.cmd, info.pipe_num);
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }
