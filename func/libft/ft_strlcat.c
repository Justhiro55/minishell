/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:40:00 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/16 13:01:05 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0 && dst == NULL)
		return (ft_strlen (src));
	while (*dst != '\0' && i < dstsize)
	{
		++dst;
		++i;
	}
	return (ft_strlcpy(dst, src, dstsize - i) + i);
}

// #include <string.h>

// int	main(void)
// {
// 	size_t i;
// 	char s1[30] = "123456";
// 	char s2[30] = "abcdef";

// 	i = ft_strlcat(s1, s2, 15);
// 	printf("ft_strlcat : %s n=%zu, ", s1, i);
// 	i = strlcat(s1, s2, 15);
// 	printf("strlcat : %s n=%zu\n", s1, i);
// 	return (0);
// }
