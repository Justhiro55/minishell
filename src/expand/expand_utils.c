/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 20:06:26 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/11/27 20:06:39 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	is_alpha_under(char c)
{
	return ((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) || c == '_');
}

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = (char *)malloc(size * sizeof(char));
	if (new == NULL)
		exit_process(EXIT_FAILURE_MALLOC);
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}
