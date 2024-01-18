/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotainou <kotainou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:29:23 by kotainou          #+#    #+#             */
/*   Updated: 2024/01/13 21:23:54 by kotainou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	error_parser(void)
{
	ft_putstr_fd("syntax error near unexpected token `\"'\n", 1);
	exit(1);
}

char	*create_text(char *text, size_t str_size)
{
	char	*new_text;
	size_t	new_i;
	size_t	old_i;

	new_text = ft_calloc(str_size + 1, sizeof(char));
	new_i = 0;
	old_i = 0;
	while (text[old_i] != 0)
	{
		if (text[old_i] == '"' || text[old_i] == '\'')
		{
			old_i++;
			continue ;
		}
		new_text[new_i] = text[old_i];
		new_i++;
		old_i++;
	}
	return (new_text);
}

char	*check_text(char *text)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < ft_strlen(text))
	{
		if (flag == 0 && (text[i] == '"' || text[i] == '\''))
		{
			if (text[i] == '"')
				flag = 0x01;
			else
				flag = 0x10;
			i++;
			continue ;
		}
		if ((flag == 0x01 && text[i] == '"') || (flag == 0x10
				&& text[i] == '\''))
			flag = 0;
		i++;
	}
	if (flag)
		error_parser();
	return (NULL);
}

t_node	*new_node_cmdname(t_now_token *ntk)
{
	t_node	*node;
	char	*cmd;
	size_t	i;

	i = 0;
	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(count_word(ntk) + 1, sizeof(char *));
	while (ntk->now != NULL && ft_strncmp(ntk->now->str, "|", 1) != 0)
	{
		if (is_redirect(ntk) && ntk->now->next != NULL)
			return (new_node_redirect(node, ntk));
		if (ntk->now == NULL)
			break ;
		cmd = ft_strdup(ntk->now->str);
		check_text(cmd);
		node->data[i] = ft_strdup(cmd);
		free(cmd);
		i++;
		node->data[i] = NULL;
		ntk->now = ntk->now->next;
	}
	node->row_size = i;
	return (node);
}

// void	printTree(t_node *root, size_t depth)
// {
// 	size_t		i;
// 	t_redirects	*tmp;
// 	int			cmd_i;

// 	cmd_i = 0;
// 	if (root == NULL)
// 		return ;
// 	printTree(root->right, depth + 1);
// 	for (i = 0; i < depth; i++)
// 		printf(" ");
// 	tmp = root->redirects;
// 	if (tmp != NULL)
// 	{
// 		while (root->data[cmd_i] != NULL)
// 		{
// 			if (cmd_i == 0)
// 				printf("cmd = ");
// 			printf(" [%s]", root->data[cmd_i]);
// 			cmd_i++;
// 		}
// 		while (tmp != NULL)
// 		{
// 			printf(" type = [%d] ", tmp->type);
// 			printf(" filename =  [%s] ", tmp->filename);
// 			tmp = tmp->next;
// 		}
// 	}
// 	for (i = 0; i < root->row_size; i++)
// 	{
// 		if (i == 0)
// 			printf("+");
// 		if (i == 0 && root->type == NODE_PIPE)
// 			printf("type pipe ");
// 		else if (i == 0 && root->type == NODE_COMMAND)
// 			printf("type cmd ");
// 		printf("%s ", root->data[i]);
// 	}
// 	printf("\n");
// 	printTree(root->left, depth + 1);
// 	depth++;
// }
