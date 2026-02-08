/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:01:09 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/23 15:01:15 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_conv(char *s, int dec, int t, int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		s[i] = '-';
		i++;
	}
	while (dec > 0)
	{
		s[i] = (t / dec) + 48;
		t = t % dec;
		dec /= 10;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	size_t	len;
	int		dec;
	int		t;
	char	*s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 1;
	dec = 1;
	t = n;
	if (t < 0)
	{
		t = -t;
		len++;
	}
	while ((t / dec) > 9)
	{
		dec *= 10;
		len++;
	}
	s = (char *)malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	return (ft_conv(s, dec, t, n));
}
