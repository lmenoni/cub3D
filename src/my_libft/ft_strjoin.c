/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:09:40 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/20 17:09:43 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	tlen;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	tlen = ft_strlen(s1) + ft_strlen(s2);
	r = (char *)malloc((tlen + 1) * sizeof(char));
	if (!r)
		return (NULL);
	while (s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		r[i + j] = s2[j];
		j++;
	}
	r[i + j] = '\0';
	return (r);
}
