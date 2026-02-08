/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:11:32 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/04 19:21:45 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printpointer(unsigned long p, int fd)
{
	char	*h;
	int		count;

	count = 0;
	if (p == 0)
	{
		write (fd, "(nil)", 5);
		return (3);
	}
	h = "0123456789abcdef";
	if (p < 16)
		write (fd, "0x", 2);
	if (p >= 16)
		count += ft_printpointer((p / 16), fd);
	write (fd, &h[p % 16], 1);
	return (count + 1);
}
