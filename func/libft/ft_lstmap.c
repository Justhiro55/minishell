/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:05:54 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/14 12:22:00 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newmap;
	t_list	*temp;

	if (lst == NULL || f == NULL)
		return (NULL);
	newmap = NULL;
	while (lst != NULL)
	{
		temp = ft_lstnew((*f)(lst->content));
		if (temp == NULL)
		{
			ft_lstclear(&newmap, del);
			return (NULL);
		}
		ft_lstadd_back(&newmap, temp);
		temp = temp->next;
		lst = lst->next;
	}
	return (newmap);
}
