/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:35:41 by lmenoni           #+#    #+#             */
/*   Updated: 2025/06/13 13:35:43 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnncmp(char *s1, char *s2, int n1, int n2)
{
	int	i;

	i = 0;
	if (n1 != n2)
		return (-1);
	while (s1[i] && s2[i] && i < n1 && s1[i] == s2[i])
		i++;
	if (i == n1)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
