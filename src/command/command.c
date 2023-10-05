/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:59:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/05 18:59:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void	set_token(t_info *info, char *line)
{
	info->token = ft_split(line, ' ');
}

t_env	env_lstnew(char *envp)
{
	t_env	newnode;
	char	**content;

	content = ft_split(envp, '=');
	newnode.key = content[0];
	newnode.value = content[1];
	newnode.next = NULL;
	return (newnode);
}

t_env	*env_lstlast(t_env *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	set_env(t_info *info, char **envp)
{
	t_env	node;
	t_env	last;
	int		i;

	i = 0;
	info->env = NULL;
	while (*envp != NULL)
	{
		node = env_lstnew(*envp);
		if (info->env == NULL)
		{
			info->env = &node;
		}
		else
		{
			last = *env_lstlast(info->env);
			last.next = &node;
			printf("%s, %s\n", last.key, last.value);
		}
		envp++;
	}
}

void	parse(char *line, char **envp)
{
	t_info	info;

	(void)envp;
	set_token(&info, line);
	set_env(&info, envp);
	if (ft_strcmp(info.token[0], "exit") == 0)
		command_exit(info.token);
	else if (ft_strcmp(info.token[0], "echo") == 0)
		command_echo(info.token);
	else if (ft_strcmp(info.token[0], "pwd") == 0)
		command_pwd(info.token);
	else if (ft_strcmp(info.token[0], "cd") == 0)
		command_cd(info.token);
	else if (ft_strcmp(info.token[0], "env") == 0)
		command_env(info.token, envp);
	else
		command_not_found(line);
	add_history(line);
	free(line);
}
