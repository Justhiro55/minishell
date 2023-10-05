/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:52:10 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/06 22:40:11 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_digit_fd(long n)
{
	int	digit;

	digit = 1;
	if (n < 0)
	{
		n = -n;
	}
	while (n / 10 > 0)
	{
		n /= 10;
		digit *= 10;
	}
	return (digit);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	number;
	int		digit;

	number = n;
	digit = get_digit_fd(number);
	if (number == 0)
		ft_putchar_fd('0', fd);
	else if (number == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (number < 0)
		{
			ft_putchar_fd('-', fd);
			number = -number;
		}
		while (digit != 0)
		{
			ft_putchar_fd('0' + number / digit, fd);
			number %= digit;
			digit /= 10;
		}
	}
}
