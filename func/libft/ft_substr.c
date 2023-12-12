/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:03:23 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/12/04 20:45:59 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	slen;
	char	*str;

	slen = ft_strlen(s);
	if (slen <= start)
		str = ft_strdup("");
	else
	{
		str = malloc(sizeof(char) * (slen - start + 1));
		if (!str)
			perror("malloc failed");
		ft_strlcpy(str, s + start, len + 1);
	}
	return (str);
}
