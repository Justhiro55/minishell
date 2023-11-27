/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 15:24:26 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/25 15:26:34 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	free_redirects(t_redirects *redirects)
{
	t_redirects	*current;

	while (redirects)
	{
		current = redirects;
		redirects = redirects->next;
		if (current->filename != NULL)
			free(current->filename);
		free(current);
	}
}

void	free_node(t_node *node)
{
	int	i;

	i = 0;
	if (node)
	{
		while (node->data[i] != NULL && i < (int)node->row_size)
		{
			free(node->data[i]);
			i++;
		}
		free(node->data);
		if (node->redirects != NULL)
			free_redirects(node->redirects);
		free_node(node->left);
		free_node(node->right);
		free(node);
	}
}

void	env_lstclear(t_env **lst)
{
	t_env	*current;
	t_env	*temp;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
	*lst = NULL;
}

void	free_info_token(t_info *info)
{
	int	i;

	if (info->token)
	{
		i = 0;
		while (info->token[i] != NULL)
		{
			free(info->token[i]);
			i++;
		}
		free(info->token);
		info->token = NULL;
	}
}

void	free_info(t_info *info)
{
	if (info)
	{
		env_lstclear(&info->env);
		free_info_token(info);
	}
}