/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:13:47 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/01 15:13:48 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ('a' <= c && c <= 'z')
	{
		return (1);
	}
	if ('A' <= c && c <= 'Z')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

// int main(){
// 	printf("%d\n", isalpha(0));
// 	printf("%d\n", isalpha('c'));
// 	printf("%d\n", isalpha('q'));

// 	return (0);
// }
