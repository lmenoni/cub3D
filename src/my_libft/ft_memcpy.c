/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:48:26 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/19 10:48:31 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *str, size_t n)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*str2;

	if (dst == NULL && str == NULL)
		return (0);
	dst2 = (unsigned char *)dst;
	str2 = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		dst2[i] = str2[i];
		i++;
	}
	return (dst);
}
