/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:44:06 by lmenoni           #+#    #+#             */
/*   Updated: 2024/11/20 18:44:11 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_counts(char const *s, char c)
{
	int		f;
	size_t	i;
	size_t	count;

	f = 0;
	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
		{
			i++;
			f = 0;
		}
		if (s[i] != c && f == 0 && s[i] != '\0')
		{
			count++;
			f = 1;
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (count);
}

static char	**ft_make(char **mat, const char *s, char c, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	f;

	i = 0;
	j = 0;
	f = 0;
	while (s[f] == c)
		f++;
	while (j < len)
	{
		while (s[i] == c)
			i++;
		f = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		mat[j] = ft_substr(s, f, (i - f));
		if (!mat[j])
			return (ft_freemat((void **)mat, j), NULL);
		j++;
	}
	mat[j] = NULL;
	return (mat);
}

char	**ft_split(char const *str, char c)
{
	char	**r;
	size_t	cnt;

	cnt = ft_counts(str, c);
	r = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!r)
		return (NULL);
	return (ft_make(r, str, c, cnt));
}
