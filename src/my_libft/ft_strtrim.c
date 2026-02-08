/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:37:11 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/20 17:37:13 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	while (i < len && ft_strchr(set, s1[i]))
		i++;
	while (i < len && ft_strchr(set, s1[len - 1]))
		len--;
	return (ft_substr(s1, i, (len - i)));
}
