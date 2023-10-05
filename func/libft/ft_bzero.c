/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:53:30 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/02 14:03:14 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char			*str;
	unsigned long	i;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

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
//     printf("%s\n", s1);
//     bzero(s1, 2);
//     int i=0;
//     for(i=0; i<5; i++){
//         printf("s1[%d] : %c\n", i, s1[i]);//コピー後のs1の表示
//     }
// }
