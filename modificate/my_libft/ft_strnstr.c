/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:01:58 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/20 12:01:59 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lil, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (lil[i] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == lil[j] && lil[j] != '\0' && (i + j) < len)
			j++;
		if (lil[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
