/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:14:32 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/16 13:12:33 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	n;
	char	*str;

	n = 0;
	str = b;
	while (n < len)
	{
		str[n] = (unsigned char)c;
		n++;
	}
	return (b);
}

// #include <stdio.h>
// int main(){
//     char s1[5];
//     memset(s1, 'a', sizeof(s1));
//     printf("%s\n", s1);
// }
