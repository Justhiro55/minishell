/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:07:26 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/16 13:11:31 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*object;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	object = malloc(size * count);
	if (object == NULL)
		return (NULL);
	ft_memset(object, 0, size * count);
	return (object);
}
