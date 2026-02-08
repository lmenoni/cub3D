/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:07:21 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/04 19:20:59 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printnbr(int n, int fd)
{
	char	h;
	int		count;

	count = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		count++;
	}
	if (n >= 10)
		count += ft_printnbr(n / 10, fd);
	h = (n % 10) + '0';
	write (fd, &h, 1);
	return (count + 1);
}
