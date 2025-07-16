/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:04:52 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/19 15:04:54 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*r;
	size_t			l;
	unsigned char	h;

	r = (char *)s;
	l = ft_strlen(r);
	h = (unsigned char) c;
	while (l > 0)
	{
		if (r[l] == h)
			return (&r[l]);
		l--;
	}
	if (r[l] == h)
		return (&r[l]);
	return (NULL);
}
