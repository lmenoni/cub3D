/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:21:27 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/19 16:21:31 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*r;

	r = (unsigned char *)s;
	while (n > 0)
	{
		if (*r == (unsigned char)c)
			return (r);
		r++;
		n--;
	}
	return (NULL);
}
