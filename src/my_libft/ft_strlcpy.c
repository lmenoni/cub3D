/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:52:14 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/18 16:52:18 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *str, size_t n)
{
	size_t	i;

	if (n != 0)
	{
		i = 0;
		while (i < (n - 1) && str[i] != '\0')
		{
			dst[i] = str[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(str));
}
