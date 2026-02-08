/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:35:27 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/13 13:35:28 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_matdup(char **mat)
{
	int		len;
	int		i;
	char	**r;

	len = ft_matlen(mat);
	i = 0;
	r = malloc((len + 1) * sizeof(char *));
	if (!r)
		return (NULL);
	while (i < len)
	{
		r[i] = ft_strdup(mat[i]);
		i++;
	}
	r[i] = NULL;
	return (r);
}
