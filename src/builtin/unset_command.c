/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:15:46 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/22 15:33:07 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	arg_check(char *token)
{
	int	i;

	i = 0;
	if (token[0] == '_')
		return (SUCCESS);
	if (ft_isalpha(token[0]) == 0)
	{
		printf("unset: \'%s\': not a valid identifier\n", token);
		return (ERROR);
	}
	while (token[i] != '\0')
	{
		if (token[i] == '=')
		{
			printf("unset: \'%s\': not a valid identifier\n", token);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

void	unset_free(t_env *current)
{
	free(current->key);
	free(current->value);
	free(current);
}

void	unset_process(char *token, t_info *info)
{
	t_env	*prev;
	t_env	*current;
	t_env	*head;

	prev = NULL;
	current = info->env;
	head = current;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, token) == 0)
		{
			if (prev == NULL)
			{
				unset_free(current);
				info->env = current->next;
				return ;
			}
			unset_free(current);
			prev->next = current->next;
		}
		prev = current;
		current = current->next;
	}
	info->env = head;
}

int	command_unset(char **token, t_info *info)
{
	int	status;
	int	i;

	i = 1;
	status = SUCCESS;
	if (token[i] == NULL)
		return (status);
	while (token[i] != NULL)
	{
		if (arg_check(token[i]) == ERROR)
			status = ERROR;
		else if (token[i][0] != '_')
			unset_process(token[i], info);
		i++;
	}
	return (status);
}
