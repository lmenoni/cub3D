/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:19:26 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:19:27 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	is_int(char *s)
{
	if (!*s)
		return (false);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		s++;
	}
	return (true);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	skip_spaces(str, &i);
	if (str[i] == '\0')
		return (true);
	return (false);
}

char	*clean_value(char	*line)
{
	int		i;
	int		j;
	char	*r;

	i = 0;
	j = 0;
	r = NULL;
	skip_spaces(line, &i);
	if (line[i] == '\0')
		return (ft_printf_fd(2, ELE_EMPTY), NULL);
	r = &line[i];
	while (!is_space(line[i]) && line[i] != '\0')
		i++;
	skip_spaces(&line[i], &j);
	if (line[i + j] != '\0')
		return (ft_printf_fd(2, ELE_VAL), NULL);
	line[i] = '\0';
	return (r);
}

bool	all_set(t_parse *parse)
{
	if (!parse->n_path || !parse->s_path
		|| !parse->e_path || !parse->w_path
		|| !parse->f_clr || !parse->c_clr)
	{
		ft_printf_fd(2, ELE_EMPTY);
		return (false);
	}
	return (true);
}
