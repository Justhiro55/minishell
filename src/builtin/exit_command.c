/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:55:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/02 19:30:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	free_redirects(t_redirects *redirects)
{
	t_redirects	*current;

	while (redirects)
	{
		current = redirects;
		redirects = redirects->next;
		if (current->filename != NULL)
			free(current->filename);
		free(current);
	}
}

void	free_node(t_node *node)
{
	int	i;

	i = 0;
	if (node)
	{
		while (node->data[i] != NULL && i < (int)node->row_size)
		{
			free(node->data[i]);
			i++;
		}
		free(node->data);
		if (node->redirects != NULL)
			free_redirects(node->redirects);
		free_node(node->left);
		free_node(node->right);
		free(node);
	}
}

void	env_lstclear(t_env **lst)
{
	t_env	*current;
	t_env	*temp;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
	*lst = NULL;
}

void	free_env_list(t_env *env)
{
	t_env	*current;

	while (env)
	{
		current = env;
		env = env->next;
		free(current->key);
		free(current->value);
		free(current);
	}
}

void	free_info(t_info *info)
{
	if (info)
	{
		env_lstclear(&info->env);
	}
}

int	command_exit(char **token, t_info *info, t_node *node)
{
	if (token[1] == NULL)
	{
		free_node(node);
		free_info(info);
		exit(0);
	}
	else if (token[2] == NULL)
	{
		free_node(node);
		free_info(info);
		exit(atoi(token[1]));
	}
	else
		ft_putstr_fd("exit: too many arguments\n", STDERR);
	return (1);
}
