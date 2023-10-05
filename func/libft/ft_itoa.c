/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 13:42:44 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/06 17:52:55 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	get_digit(long n)
{
	int	digit;

	digit = 0;
	if (n < 0)
	{
		n = -n;
		digit++;
	}
	while (n > 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

char	*set_zero(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long	number;
	int		count;
	char	*str;

	number = n;
	count = get_digit(number);
	if (number == 0)
		return (set_zero());
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (NULL);
	str[count--] = '\0';
	if (number < 0)
	{
		str[0] = '-';
		number = -number;
	}
	while (number > 0)
	{
		str[count] = '0' + number % 10;
		number /= 10;
		count--;
	}
	return (str);
}
