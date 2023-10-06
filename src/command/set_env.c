/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:26:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/06 18:31:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

t_env	*env_lstnew(char *envp)
{
	char	**content;
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node)
	{
		content = ft_split(envp, '=');
		new_node->key = content[0];
		new_node->value = content[1];
		new_node->next = NULL;
	}
	return (new_node);
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
	t_env	*first;
	t_env	*last;
	t_env	*new_node;

	first = NULL;
	last = NULL;
	info->env = NULL;
	while (*envp != NULL)
	{
		new_node = env_lstnew(*envp);
		if (!new_node)
			break ;
		new_node->next = NULL;
		if (info->env == NULL)
		{
			info->env = new_node;
			first = new_node;
		}
		else
		{
			last->next = new_node;
		}
		last = new_node;
		envp++;
	}
	// printf("%s, %s\n", info->env->key, info->env->value);
	// printf("%s, %s\n", info->env->next->key, info->env->next->value);
	// printf("%s, %s\n", info->env->next->next->key,
	// 		info->env->next->next->value);
}
