/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:40:00 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/11 14:08:38 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	error_export_msg(char *str)
{
	ft_putstr_fd("bash: export:\'", STDERR);
	ft_putstr_fd(str, STDERR);
	ft_putstr_fd("\': not a valid identifier\n", STDERR);
	return (ERROR);
}

int	export_error(char **token)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (token[i] != NULL)
	{
		while (token[i][j] != '\0')
		{
			if (token[i][j] == '=')
			{
				if (j == 0)
					return (error_export_msg(token[i]));
			}
			break ;
			j++;
		}
		if (j == (int)ft_strlen(token[i]))
			return (ERROR);
		j = 0;
		i++;
	}
	return (0);
}

int	export_node(t_info *info, t_env new_node)
{
	t_env	*tmp;

	tmp = info->env;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, new_node.key) == 0)
		{
			tmp->value = new_node.value;
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
		printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
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
	if (export_error(token) == ERROR)
		return (error_export_msg(token[1]));
	while (token[i] && (i++))
	{
		if (token[i - 1][0] != '_')
		{
			if (ft_isalpha(token[i - 1][0]) == 0)
				result = error_export_msg(token[i - 1]);
			else
			{
				new_node = env_lstnew(token[i - 1]);
				if (new_node && export_node(info, *new_node) == SUCCESS)
					env_add_back(info, new_node);
			}
		}
	}
	return (result);
}
