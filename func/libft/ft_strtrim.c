/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:52:37 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/16 13:01:47 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	get_trim_start(char const *s1, char const *set)
// {
// 	int	i;
// 	int	start;

// 	i = 0;
// 	start = 0;
// 	while (s1[start] != '\0')
// 	{
// 		while (set[i] != '\0')
// 		{
// 			if (s1[start] == set[i])
// 			{
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (set[i] == '\0')
// 			break ;
// 		i = 0;
// 		start++;
// 	}
// 	return (start);
// }

int	is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[start] && is_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && is_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
