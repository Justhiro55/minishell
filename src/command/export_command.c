/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:40:00 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/07 15:46:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

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
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	command_export(char **token, t_info info)
{
	t_env	*new_node;

	if (token[1] == NULL)
	{
		ft_putstr_fd("export: not enough arguments\n", STDERR);
		return (1);
	}
	if (token[1] != NULL)
	{
		if (export_error(token) == ERROR)
			printf("ERROR\n");
		new_node = env_lstnew(token[1]);
		if (export_node(&info, *new_node) == 0)
			env_add_back(&info, new_node);
		env_lstlast(info.env)->next = NULL;
	}
	return (0);
}