/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:14:24 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/02 17:14:57 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*strdst;
	const char	*strsrc;

	if (dst == NULL && src == NULL)
		return (NULL);
	strsrc = src;
	strdst = dst;
	i = 0;
	if (strsrc > strdst)
	{
		ft_memcpy(dst, src, len);
	}
	else
	{
		while (i++ < len)
		{
			strdst[len - i] = strsrc[len - i];
		}
	}
	return (dst);
}
