/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:21:33 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/16 13:01:14 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dstsize != 0 && src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (ft_strlen(src));
}

// #include <string.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	size_t	i;
// 	char *dst1 = calloc(10, sizeof(char));
// 	char *dst2 = calloc(10, sizeof(char));
// 	char *src1 = calloc(10, sizeof(char));
// 	char *src2 = calloc(10, sizeof(char));
// 	char *s1 = "hello";
// 	char *s2 = "hello wonderfule world!";
// 	memset(src1, 'z', 9);
// 	memset(src2, 'z', 9);

// 	i = ft_strlcpy(dst1, s1, 0);
// 	printf("ft_strlcpy : %s n=%zu, ", dst1, i);
//     i = ft_strlcpy(dst1, s1, 0);
// 	printf("strlcpy : %s n=%zu\n", dst1, i);
// 	return (0);
// }
