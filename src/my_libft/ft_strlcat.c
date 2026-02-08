/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:08:29 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/19 17:08:32 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *d, const char *s, size_t size)
{
	size_t	tl;
	size_t	i;

	if (size <= ft_strlen(d))
		return (ft_strlen(s) + size);
	tl = ft_strlen(s) + ft_strlen(d);
	while (*d)
		d++;
	i = 0;
	while (i < (size - (tl - ft_strlen(s)) - 1) && s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (tl);
}
