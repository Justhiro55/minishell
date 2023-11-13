/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:40:44 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/13 19:27:37 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

t_node	*create_node(void)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		exit_process(EXIT_FAILURE_MALLOC);
	ft_memset(new_node, 0, sizeof(t_node));
	return (new_node);
}

t_redirects	*create_redirects(void)
{
	t_redirects	*new_redirects;

	new_redirects = (t_redirects *)malloc(sizeof(t_redirects));
	if (!new_redirects)
		exit_process(EXIT_FAILURE_MALLOC);
	ft_memset(new_redirects, 0, sizeof(t_redirects));
	new_redirects->fd_file = -1;
	new_redirects->fd_backup = ft_dup(STDOUT_FILENO);
	return (new_redirects);
}


void	set_node(t_node *node)
{
	t_node	*node_child1;
	t_node	*node_child2;
	t_node	*node_child3;
	t_node	*node_child4;
	t_node	*node_pipe_1;
	t_node	*node_pipe_2;

	node_child1 = create_node();
	node_child2 = create_node();
	node_child3 = create_node();
	node_child4 = create_node();
	node_pipe_1 = create_node();
	node_pipe_2 = create_node();
	// nodeのdataを設定
	node->data = (char **)malloc(sizeof(char *) * 2);
	node->data[0] = strdup("pipe");
	node->data[1] = NULL;
	node->type = NODE_PIPE;
	// node_child1の設定
	node_child1->data = (char **)malloc(sizeof(char *) * 4);
	node_child1->data[0] = strdup("head");
	node_child1->data[1] = strdup("-n");
	node_child1->data[2] = strdup("333");
	node_child1->data[3] = NULL;
	node_child1->type = NODE_COMMAND;
	node_child1->redirects = create_redirects();
	node_child1->redirects->next = NULL;
	// node_child2の設定
	node_child2->data = (char **)malloc(sizeof(char *) * 2);
	node_child2->data[0] = strdup("cat");
	node_child2->data[1] = NULL;
	node_child2->type = NODE_COMMAND;
	node_child2->redirects = create_redirects();
	// node_child2->redirects->type = REDIRECT_INPUT;
	node_child2->redirects->type = REDIRECT_HEREDOC;
	node_child2->redirects->filename = strdup("src/exec/exec.c");
	node_child2->redirects->next = create_redirects();
	node_child2->redirects->next->type = REDIRECT_HEREDOC;
	// node_child2->redirects->next->type = REDIRECT_INPUT;
	node_child2->redirects->next->filename = strdup("end");
	node_child2->redirects->next->next = NULL;


	
	// node_child2->redirects->next->next = create_redirects();
	// node_child2->redirects->next->next->next = NULL;
	// node_child2->redirects->next->next->type = REDIRECT_OUTPUT;
	// node_child2->redirects->next->next->filename = strdup("test");
	// node_child2->redirects->next->next->fd_file = open_file(node_child2->redirects->next->next);



	
	// node_child3の設定
	node_child3->data = (char **)malloc(sizeof(char *) * 2);
	node_child3->data[0] = strdup("cat");
	node_child3->data[1] = NULL;
	node_child3->type = NODE_COMMAND;
	node_child3->redirects = create_redirects();
	node_child3->redirects->type = REDIRECT_OUTPUT;
	node_child3->redirects->filename = strdup("test_outfile1");
	node_child3->redirects->fd_file = open_file(node_child3->redirects);
	node_child3->redirects->type = REDIRECT_OUTPUT;


	node_child3->redirects->next = create_redirects();
	node_child3->redirects->next->type = REDIRECT_OUTPUT;
	node_child3->redirects->next->filename = strdup("test_outfile2");
	node_child3->redirects->next->fd_file = open_file(node_child3->redirects->next);
	node_child3->redirects->next->next = NULL;

	
	// node_child4の設定
	node_child4->data = (char **)malloc(sizeof(char *) * 4);
	node_child4->data[0] = strdup("cat");
	node_child4->data[1] = NULL;
	node_child4->type = NODE_COMMAND;
	node_child4->redirects = create_redirects();
	node_child4->redirects->next = NULL;
	// node_pipe_1とnode_pipe_2の設定
	node_pipe_1->data = (char **)malloc(sizeof(char *) * 2);
	node_pipe_1->data[0] = strdup("pipe");
	node_pipe_1->data[1] = NULL;
	node_pipe_1->type = NODE_PIPE;
	node_pipe_2->data = (char **)malloc(sizeof(char *) * 2);
	node_pipe_2->data[0] = strdup("pipe");
	node_pipe_2->data[1] = NULL;
	node_pipe_2->type = NODE_PIPE;
	// ノードの接続
	node->left = node_pipe_1;
	node->right = node_child3;
	node_pipe_1->right = node_child1;
	node_pipe_1->left = node_pipe_2;
	node_pipe_2->right = node_child4;
	node_pipe_2->left = node_child2;
	node_child1->left = NULL;
	node_child1->right = NULL;
	node_child2->left = NULL;
	node_child2->right = NULL;
	node_child3->left = NULL;
	node_child3->right = NULL;
	node_child4->left = NULL;
	node_child4->right = NULL;
}
