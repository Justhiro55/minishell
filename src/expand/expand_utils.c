/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:06:26 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/12 17:38:16 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	handle_special_char(char **dst, char **rest, t_info *info);
int	is_alpha_under(char c);
void	append_char(char **s, char c);

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

int	handle_env_variable(char **dst, char **rest, t_info *info)
{
	char	*value;
	char	*value_iter;

	if (get_env(*rest, info->env) == NULL)
		return (-1);
	value = ft_strdup(get_env(*rest, info->env));
	if (value)
	{
		value_iter = value;
		while (*value_iter != '\0')
			append_char(dst, *(value_iter++));
		free(value);
	}
	return (0);
}

int	handle_special_char(char **dst, char **rest, t_info *info)
{
	char	*value;
	char	*value_iter;

	*rest += 1;
	value = ft_itoa(info->status);
	if (value)
	{
		value_iter = value;
		while (*value_iter != '\0')
			append_char(dst, *(value_iter++));
		free(value);
	}
	return (0);
}

int	is_variable(char **dst, char **rest, char *p, t_info *info)
{
	(void)p;
	if (**rest == '$')
	{
		(*rest)++;
		if (is_alpha_under(**rest))
		{
			return (handle_env_variable(dst, rest, info));
		}
		else if (**rest == '?')
		{
			return (handle_special_char(dst, rest, info));
		}
		else
			append_char(dst, '$');
	}
	return (1);
}
