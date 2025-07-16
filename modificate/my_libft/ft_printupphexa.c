/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printupphexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:05:34 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/04 19:22:31 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printupphexa(unsigned int n, int fd)
{
	char	*h;
	int		count;

	count = 0;
	h = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_printupphexa(n / 16, fd);
	write (fd, &h[n % 16], 1);
	return (count + 1);
}
