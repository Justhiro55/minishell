/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:26:57 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/25 17:38:48 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*ft_strndup(const char *s, size_t n);

void	remove_quotes_in_place(char *str)
{
	int	read_index;
	int	write_index;

	read_index = 0;
	write_index = 0;
	while (str[read_index] != '\0')
	{
		if (str[read_index] != '"')
		{
			str[write_index] = str[read_index];
			write_index++;
		}
		read_index++;
	}
	str[write_index] = '\0';
}

t_env	*env_lstnew(char *envp)
{
	t_env	*new_node;
	char	*separator;
	int		key_length;

	new_node = (t_env *)malloc(sizeof(t_env));
	remove_quotes_in_place(envp);
	if (new_node)
	{
		separator = ft_strchr(envp, '=');
		remove_quotes_in_place(separator);
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
