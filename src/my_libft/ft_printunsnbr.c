/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsnbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 11:57:36 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/04 19:22:03 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printunsnbr(unsigned int n, int fd)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 10)
		count += ft_printunsnbr(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
	return (count + 1);
}
