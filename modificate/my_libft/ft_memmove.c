/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:05:28 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/19 11:05:30 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *str, size_t n)
{
	unsigned char	*str2;
	unsigned char	*dst2;
	size_t			i;

	str2 = (unsigned char *)str;
	dst2 = (unsigned char *)dst;
	if (str2 > dst2)
		dst = ft_memcpy(dst2, str2, n);
	if (str2 < dst2)
	{
		i = n;
		while (i > 0)
		{
			i--;
			dst2[i] = str2[i];
		}
	}
	return (dst);
}
