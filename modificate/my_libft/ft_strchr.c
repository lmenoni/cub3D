/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:52:39 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/19 14:52:41 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*r;

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
