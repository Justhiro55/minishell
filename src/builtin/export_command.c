/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:40:00 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/01/13 20:46:10 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_strchr_export(const char *s, int c);

int	error_export_msg(char *str)
{
	if (str[0] == '-' && str[1] != '\0')
	{
		ft_putstr_fd("bash: export:\'", STDERR);
		ft_putstr_fd(str, STDERR);
		ft_putstr_fd("\': invalid option\n", STDERR);
		return (2);
	}
	ft_putstr_fd("bash: export:\'", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("\': not a valid identifier\n", STDERR);
	return (ERROR);
}

int	export_error(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '=')
		{
			if (i == 0)
				return (ERROR);
		}
		i++;
		break ;
	}
	return (0);
}

int	export_node(t_info *info, t_env *new_node)
{
	t_env	*tmp;

	tmp = info->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, new_node->key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_node->value);
			free(new_node->key);
			free(new_node->value);
			free(new_node);
			return (ERROR);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	export_one_arg(t_info *info)
{
	t_env	*tmp;

	tmp = info->env;
	while (tmp != NULL)
	{
		if (tmp->value != NULL && tmp->value[0] != '\0' && tmp->key[0] != '_')
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->key[0] != '_')
			printf("declare -x %s=\"\"\n", tmp->key);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	command_export(char **token, t_info *info)
{
	t_env	*new_node;
	int		result;
	int		i;

	i = 1;
	result = SUCCESS;
	if (token[1] == NULL)
		return (export_one_arg(info));
	while (token[i] && (i++))
	{
		if ((ft_isalpha(token[i - 1][0]) == 0 && token[i - 1][0] != '_')
			|| token[i - 1][0] == '=' || token[i - 1][ft_strlen(token[i - 1])
			- 1] == '-' || ft_strchr_export(token[i - 1], '=') == 1)
			result = error_export_msg(token[i - 1]);
		else
		{
			new_node = env_lstnew(token[i - 1]);
			if (new_node && export_node(info, new_node) == SUCCESS)
				env_add_back(info, new_node);
		}
	}
	return (result);
}
