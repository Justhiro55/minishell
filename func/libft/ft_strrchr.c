/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:48:09 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/16 13:01:58 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*set_pointer(char *s, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		s++;
		i++;
	}
	return (s);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == '\0')
		return (set_pointer((char *)s, i));
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (set_pointer((char *)s, i));
		i--;
	}
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*s1;
// 	int		i2;
// 	char	*result;

// 	s1 = "\0";
// 	i2 = 'a';
// 	result = ft_strrchr(s1, i2);
// 	printf("%s \n", result);
// 	return (0);
// }
