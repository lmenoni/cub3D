/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:01:55 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/20 14:02:00 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t slot, size_t size)
{
	void	*t;

	if (slot * size > INT_MAX)
		return (NULL);
	t = (void *)malloc(slot * size);
	if (!t)
		return (NULL);
	ft_bzero(t, slot * size);
	return (t);
}
