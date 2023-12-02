/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:26:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/02 19:38:30 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

t_env	*env_lstnew(char *envp)
{
	char	**content;
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node)
	{
		content = ft_split(envp, '=');
		new_node->key = strdup(content[0]);
		if (content[1] == NULL)
			new_node->value = strdup("");
		else
			new_node->value = strdup(content[1]);
		new_node->next = NULL;
		ft_free_array(content);
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

void	env_add_back(t_info *info, t_env *new_node)
{
	t_env	*last;

	if (info->env == NULL)
		info->env = new_node;
	else
	{
		last = env_lstlast(info->env);
		if (last)
			last->next = new_node;
	}
}

void	set_env(t_info *info, char **envp)
{
	t_env	*last;
	t_env	*new_node;

	last = NULL;
	info->status = 0;
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
		}
		else
			last->next = new_node;
		last = new_node;
		envp++;
	}
}
