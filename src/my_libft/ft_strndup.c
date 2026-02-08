/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <lmenoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:20:27 by lmenoni           #+#    #+#             */
/*   Updated: 2025/05/19 16:19:23 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*r;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len > n)
		len = n;
	r = (char *)malloc((len + 1) * sizeof(char));
	if (!r)
		return (NULL);
	while (i < len)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
