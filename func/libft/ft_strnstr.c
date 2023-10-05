/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:35:24 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/16 13:02:01 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_pointer(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	size = ft_strlen(to_find);
	while (str[i] != '\0' && i < len && size <= len - i)
	{
		if (str[i] == to_find[0])
		{
			while (str[i + j] == to_find[j] && j < len)
			{
				if (j == size - 1)
					return (i);
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (-1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	pointer;

	if (haystack == NULL && len < 1)
		return (NULL);
	else if (needle[0] == '\0')
		return ((char *)haystack);
	pointer = is_pointer(haystack, needle, len);
	if (pointer == -1)
		return (NULL);
	return ((char *)haystack + pointer);
}
