/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:43:49 by lmenoni           #+#    #+#             */
/*   Updated: 2025/01/24 14:43:58 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_find(const char *s, int c)
{
	char	*r;

	if (!s)
		return (NULL);
	r = (char *)s;
	while (*r != '\0')
	{
		if ((unsigned char)*r == (unsigned char)c)
			return (r);
		r++;
	}
	if (*r == c)
		return (r);
	return (NULL);
}
