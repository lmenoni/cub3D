/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:42:27 by lmenoni           #+#    #+#             */
/*   Updated: 2025/01/24 14:42:59 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_buffjoin(char *s1, char *s2)
{
	char	*r;
	size_t	tlen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tlen = ft_bufflen(s1) + ft_bufflen(s2);
	r = (char *)malloc((tlen + 1) * sizeof(char));
	if (!r)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
	{
		r[i + j] = s2[j];
		j++;
	}
	r[i + j] = '\0';
	return (free(s1), r);
}
