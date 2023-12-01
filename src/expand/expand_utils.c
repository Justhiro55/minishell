/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:06:26 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/01 19:42:30 by hhagiwar         ###   ########.fr       */
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
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(key);
	if (tmp == NULL)
		return (NULL);
	while (tmp[i] != '\0' && tmp[i] != '\"' && tmp[i] != '$')
		i++;
	tmp[i] = '\0';
	while (env != NULL)
	{
		if (ft_strcmp(env->key, tmp) == 0)
		{
			free(tmp);
			return (env->value);
		}
		env = env->next;
	}
	free(tmp);
	return (NULL);
}

int	is_variable(char **dst, char **rest, char *p, t_info *info)
{
	char	*value;
	int		num;

	(void)p;
	num = 1;
	if (**rest == '$')
	{
		(*rest)++;
		if (is_alpha_under(**rest))
		{
			if (get_env(*rest, info->env) == NULL)
				return (-1);
			value = ft_strdup(get_env(*rest, info->env));
			if (value)
			{
				while (*value != '\0' && is_alpha_under(*value))
					append_char(dst, *(value++));
			}
		}
		else if (**rest == '?')
		{
			*rest += 1;
			value = ft_itoa(info->status);
			while (*value != '\0')
				append_char(dst, *(value++));
		}
		else
			append_char(dst, '$');
	}
	return (num);
}
