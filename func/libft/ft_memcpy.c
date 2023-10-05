/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:14:17 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/02 15:41:47 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	const char	*strsrc;
	char		*strdst;

	if (dst == NULL && src == NULL)
		return (NULL);
	strsrc = src;
	strdst = dst;
	i = 0;
	while (i < n)
	{
		strdst[i] = strsrc[i];
		i++;
	}
	return (dst);
}

// void *ft_memcpy(void* dst, const void* src, unsigned long n)
// {
//     unsigned long i;
//     const char *strsrc;
//     char *strdst;

//     strsrc = (const char*)src;
//     strdst = (char*)dst;
//     i = 0;
//     while (i < n && strsrc[i] != '\0')
//     {
//         strdst[i] = strsrc[i];
//         i++;
//     }
//     return (dst);
// }

// void *memset(void *b, int c, unsigned long len)
// {
//     unsigned long n;
//     char *str;

//     n = 0;
//     str = b;
//     while(n < len)
//     {
//         str[n] = c;
//         n++;
//     }
//     str[n] = '\0';
//     return (b);
// }

// #include <stdio.h>
// int main(){
//     char s1[5];
//     memset(s1, 'a', sizeof(s1));
//     printf("s1 : %s\n", s1);
//     char s2[5];
//     memset(s2, 'b', sizeof(s2));
//     printf("s2 : %s\n", s2);
//     ft_memcpy(s1, s2, 3);
//     printf("s1_after : %s\n", s1);
// }
