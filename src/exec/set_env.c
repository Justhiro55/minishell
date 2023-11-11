/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:26:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/11 13:11:24 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = (char *)malloc(n + 1);
	if (!copy)
	{
		return (NULL);
	}
	while (i < n && s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

t_env	*env_lstnew(char *envp)
{
	t_env	*new_node;
	char	*separator;
	int		key_length;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node)
	{
		separator = ft_strchr(envp, '=');
		if (separator != NULL)
		{
			key_length = separator - envp;
			new_node->key = ft_strndup(envp, key_length);
			new_node->value = ft_strdup(separator + 1);
		}
		else
		{
			new_node->key = ft_strdup(envp);
			new_node->value = ft_strdup("");
		}
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
			last->next = new_node;
		last = new_node;
		envp++;
	}
}
