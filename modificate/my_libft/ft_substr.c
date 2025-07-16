/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:25:09 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/20 16:25:12 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;
	size_t	tlen;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	tlen = ft_strlen(s) - start;
	if (tlen > len)
		tlen = len;
	r = (char *)malloc((tlen + 1) * sizeof(char));
	if (!r)
		return (NULL);
	i = 0;
	while (i < tlen && s[start + i] != '\0')
	{
		r[i] = s[start + i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
