/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/31 16:54:50 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	set_token(t_info *info, char *line)
{
	info->token = ft_split(line, ' ');
}

int	builtin_command(t_info *info)
{
	if (ft_strcmp(info->token[0], "exit") == 0)
		command_exit(info->token);
	else if (ft_strcmp(info->token[0], "echo") == 0)
		command_echo(info->token);
	else if (ft_strcmp(info->token[0], "pwd") == 0)
		command_pwd(info->token);
	else if (ft_strcmp(info->token[0], "cd") == 0)
		command_cd(info->token);
	else if (ft_strcmp(info->token[0], "env") == 0)
		command_env(info->token, *info);
	else if (ft_strcmp(info->token[0], "export") == 0)
		command_export(info->token, info);
	// else if (ft_strcmp(info->token[0], "ls") == 0)
	// 	command_ls(getcwd(NULL, 0));
	else
		return (1);
	return (0);
}

int	ft_exec(char **command, char **envp, t_info *info)
{
	char	**path;
	int		i;
	t_env	*env;
	char	*command_path;

	i = 0;
	env = info->env;
	while (env != NULL && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	path = ft_split(env->value, ':');
	i = 0;
	while (path[i] != NULL)
	{
		command_path = ft_strjoin(ft_strjoin(path[i], "/"), command[0]);
		if (access(command_path, F_OK) == 0 && access(command_path, X_OK) == 0)
		{
			execve(command_path, command, envp);
			return (0);
		}
		free(command_path);
		i++;
	}
	return (1);
}

void	set_data(t_node *node)
{
	t_node	*node_child1;
	t_node	*node_child2;
	t_node	*node_child3;
	t_node	*node_child4;
	t_node	*node_pipe_1;
	t_node	*node_pipe_2;
	//malloc
	///command node
	node_child1 = (t_node *)malloc(sizeof(t_node));
	node_child2 = (t_node *)malloc(sizeof(t_node));
	node_child3 = (t_node *)malloc(sizeof(t_node));
	node_child4 = (t_node *)malloc(sizeof(t_node));
	node_child1->data = (char **)malloc(sizeof(char *) * 3);
	node_child2->data = (char **)malloc(sizeof(char *) * 3);
	node_child3->data = (char **)malloc(sizeof(char *) * 2);
	node_child4->data = (char **)malloc(sizeof(char *) * 4);
	///pipe node malloc
	node->data = (char **)malloc(sizeof(char *) * 2);
	node_pipe_1 = (t_node *)malloc(sizeof(t_node));
	node_pipe_2 = (t_node *)malloc(sizeof(t_node));
	node_pipe_1->data = (char **)malloc(sizeof(char *) * 2);
	node_pipe_2->data = (char **)malloc(sizeof(char *) * 2);
	//set data
	node->data[0] = strdup("pipe");
	node->data[1] = NULL;
	node_child1->data[0] = strdup("grep");
	node_child1->data[1] = strdup("int");
	node_child1->data[2] = NULL;
	node_child2->data[0] = strdup("cat");
	node_child2->data[1] = strdup("src/pipe/pipe_utils.c");
	node_child2->data[2] = NULL;
	node_child3->data[0] = strdup("wc");
	node_child3->data[1] = NULL;
	node_child4->data[0] = strdup("head");
	node_child4->data[1] = strdup("-n");
	node_child4->data[2] = strdup("32");
	node_child4->data[3] = NULL;
	node_pipe_1->data[0] = strdup("pipe");
	node_pipe_1->data[1] = NULL;
	node_pipe_2->data[0] = strdup("pipe");
	node_pipe_2->data[1] = NULL;
	//link
	node->left = node_pipe_1;
	node->right = node_child3;
	node_pipe_1->right = node_child1;
	node_pipe_1->left = node_pipe_2;
	node_pipe_2->right = node_child4;
	node_pipe_2->left = node_child2;
	node_child1->left = NULL;
	node_child1->right = NULL;
	node_child2->left = NULL;
	node_child2->right = NULL;
	node_child3->left = NULL;
	node_child3->right = NULL;
	node_child4->left = NULL;
	node_child4->right = NULL;
}

void	child_process(t_info info, char **envp, t_node *node)
{
	pid_t	parent;
	int		pipe_fd[2];
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	parent = fork();
	if (parent == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (!parent)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		if (ft_strcmp(node->left->data[0], "pipe") == 0)
			child_process(info, envp, node->left);
		else
			ft_exec(node->left->data, envp, &info);
		exit(0);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		ft_exec(node->right->data, envp, &info);
		wait(&status);
		printf("status:%d\n", status);
	}
}

void	parse(char *line, t_info *info, char **envp)
{
	t_node	*node;

	set_token(info, line);
	node = (t_node *)malloc(sizeof(t_node));
	set_data(node);
	if (ft_strcmp(node->data[0], "pipe") == 0)
	{
		child_process(*info, envp, node);
	}
}
