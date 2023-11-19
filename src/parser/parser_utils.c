/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:23:50 by kotainou          #+#    #+#             */
/*   Updated: 2023/11/17 15:36:03 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_node	*new_node(char *str, t_node *left, t_node *right)
{
	t_node	*node;

	// printf("new node= [%s]\n", right->data[0]);
	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(1, sizeof(char *));
	node->data[0] = ft_strdup(str);
	node->left = left;
	node->right = right;
	node->row_size = 1;
	node->type = NODE_PIPE;
	return (node);
}

t_node	*new_node_cmd(t_now_token *ntk)
{
	t_node	*node;

	// printf("new node cmd = [%s]\n", str);
	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(1, sizeof(char *));
	node->data[0] = ft_strdup(ntk->now->str);
	node->row_size = 1;
	ntk->now = ntk->now->next;
	return (node);
}

t_node	*new_node_cmdname(t_now_token *ntk)
{
	t_node	*node;
	char	*cmd;
	size_t	i;

	i = 0;
	node = ft_calloc(1, sizeof(t_node));
	node->data = (char **)ft_calloc(1, sizeof(char *));
	while (ntk->now != NULL && ft_strncmp(ntk->now->str, "|", 1) != 0)
	{
		if (is_redirect(ntk))
		{
			return (new_node_redirect(node, ntk));
		}
		cmd = ft_strdup(ntk->now->str);
		// printf("cmd name = [%s]\n", cmd);
		check_text(cmd);
		node->data[i] = cmd;
		i++;
		ntk->now = ntk->now->next;
	}
	node->row_size = i;
	return (node);
}

void	error_parser(void)
{
	ft_putstr_fd("error\n", 1);
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
	// printf("new str= [%s]\n", new_text);
	return (new_text);
}

char	*check_text(char *text)
{
	size_t	i;
	int		flag;
	int		quote_num;

	// char	*new_text;
	i = 0;
	flag = 0;
	quote_num = 0;
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
		{
			flag = 0;
			quote_num += 2;
		}
		i++;
	}
	if (flag)
	{
		printf("text = [%c]\n", text[i]);
		error_parser();
	}
	// printf("strlen = [%lu]\n", ft_strlen(text) - quote_num);
	// create_text(text, ft_strlen(text) - quote_num);
	// printf("create_text = [%s]\n", create_text(text, ft_strlen(text)
	// - quote_num));
	return (NULL);
}

void	printTree(t_node *root, size_t depth)
{
	size_t		i;
	t_redirects	*tmp;

	if (root == NULL)
		return ;
	printTree(root->right, depth + 1);
	for (i = 0; i < depth; i++)
		printf(" ");
	tmp = root->redirects;
	if (tmp != NULL)
	{
		// 	// while (tmp != NULL)
		// 	// {
		printf("cmd = [%s]", root->data[0]);
		printf("redirects filename =  [%s] ", root->redirects->filename);
		printf(" type = [%d] ", root->redirects->type);
		// 		tmp = tmp->next;
		// 	// }
	}
	for (i = 0; i < root->row_size; i++)
	{
		if (i == 0)
			printf("+");
		if (i == 0 && root->type == NODE_PIPE)
			printf("type PIPE ");
		else if (i == 0 && root->type == NODE_COMMAND)
			printf("type COMMAND ");
		printf("%s ", root->data[i]);
	}
	printf("\n");
	printTree(root->left, depth + 1);
	depth++;
}
