/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:45:35 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/10/02 14:39:11 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	count_skip(const char *str, char charset)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == charset)
			str++;
		if (*str != '\0')
			count++;
		while (*str != '\0' && *str != charset)
			str++;
	}
	return (count);
}

int	ft_strlen_split(const char *str, char charset)
{
	int	length;

	length = 0;
	while (str[length] != '\0' && str[length] != charset)
		length++;
	return (length);
}

char	*set_words(char *str, char charset)
{
	int		length;
	char	*word;
	int		i;

	length = ft_strlen_split(str, charset);
	word = (char *)malloc(sizeof(char) * (length + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		word[i] = str[i];
		i++;
	}
	word[length] = '\0';
	return (word);
}

char	**array_free(char **array)
{
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *str, char charset)
{
	char	**result;
	int		i;

	if (str == NULL)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_skip(str, charset) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*str != '\0')
	{
		while (*str != '\0' && *str == charset)
			str++;
		if (*str != '\0')
		{
			result[i] = set_words((char *)str, charset);
			if (result[i] == NULL)
				return (array_free(result));
			i++;
		}
		while (*str != '\0' && *str != charset)
			str++;
	}
	result[i] = NULL;
	return (result);
}
