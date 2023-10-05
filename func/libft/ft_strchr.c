/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:30:40 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/05 17:17:00 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main(){
// 	char *s = "libft-test-tokyo";
// 	printf("ft:%s, strchr:%s \n", ft_strchr(s, 'i' + 256), strchr(s, 'i'
//				+ 256));
// 	printf("ft:%s, strchr:%s \n", ft_strchr(s, 't'), strchr(s, 't'));
// 	printf("ft:%s, strchr:%s \n", ft_strchr(s, '\0'), strchr(s, '\0'));
// 	printf("ft:%s, strchr:%s \n", ft_strchr(s, 't' + 256), strchr(s, 't'
//				+ 256));
// 	return (0);
// }
