/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:36:14 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/04 19:22:17 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa(unsigned int n, int fd)
{
	char	*h;
	int		count;

	count = 0;
	h = "0123456789abcdef";
	if (n >= 16)
		count += ft_printhexa(n / 16, fd);
	write (fd, &h[n % 16], 1);
	return (count + 1);
}
