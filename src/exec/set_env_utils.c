/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:22:43 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/19 18:05:34 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_strchr_export(const char *s, int c)
{
	char	tmp;

	tmp = '\0';
	while (*s)
	{
		if (*s == (char)c)
		{
			if (tmp == '-')
				return (1);
		}
		tmp = *s;
		s++;
	}
	if (*s == '\0' && c == '\0')
		return (0);
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	i;

	i = 0;
	copy = (char *)malloc(n + 1);
	if (!copy)
	{
		return (NULL);
	}
	while (i < n && s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
