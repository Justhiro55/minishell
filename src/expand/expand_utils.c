/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:06:26 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/28 15:36:34 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_alpha_under(char c)
{
	return ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) || c == '_');
}

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = (char *)malloc(size * sizeof(char));
	if (new == NULL)
		exit_process(EXIT_FAILURE_MALLOC);
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

int	is_metacharacter(char c)
{
	return (c && strchr("|&;()<> \t\n", c));
}

char	*get_env(char *key, t_env *env)
{
	if (key == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	is_variable(char **dst, char **rest, char *p, t_env *env)
{
	char	*value;

	if (*p == '$')
	{
		(*rest)++;
		if (is_alpha_under(**rest))
		{
			value = ft_strdup(get_env(*rest, env));
			if (value)
			{
				while (*value != '\0' && is_alpha_under(*value))
					append_char(dst, *(value++));
				return (1);
			}
		}
		// else if (**rest == '?')
		// {
		// 	*rest += 1;
		// 	append_str(dst, ft_itoa(g_exit_status));
		// 	return (1);
		// }
		else
			append_char(dst, '$');
	}
	return (0);
}
