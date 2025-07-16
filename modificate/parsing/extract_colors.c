/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:18:52 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:18:53 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	check_int(char **comp, int *r, int *g, int *b)
{
	int	i;

	i = 0;
	if (ft_matlen(comp) != 3)
		return (false);
	while (comp[i])
	{
		if (!is_int(comp[i]))
			return (false);
		i++;
	}
	*r = ft_atoi(comp[0]);
	*g = ft_atoi(comp[1]);
	*b = ft_atoi(comp[2]);
	if (*r < 0 || *r > 255
		|| *g < 0 || *g > 255
		|| *b < 0 || *b > 255)
		return (false);
	return (true);
}

bool	check_syntax(char *s)
{
	int		i;
	bool	comma;

	i = 0;
	comma = false;
	if (s[i] == ',')
		return (false);
	while (s[i])
	{
		if (s[i] == ',')
		{
			if (comma)
				return (false);
			comma = true;
		}
		else
			comma = false;
		i++;
	}
	if (comma)
		return (false);
	return (true);
}

int	convert_color(char *s)
{
	int		r;
	int		g;
	int		b;
	char	**cmpnts;

	r = 0;
	g = 0;
	b = 0;
	if (!check_syntax(s))
		return (ft_printf_fd(2, CLR_SYN), -1);
	cmpnts = ft_split(s, ',');
	if (!cmpnts)
		return (ft_printf_fd(2, E_ALLOC), -1);
	if (!check_int(cmpnts, &r, &g, &b))
	{
		ft_freemat((void **)cmpnts, ft_matlen(cmpnts));
		return (ft_printf_fd(2, CLR_VAL), -1);
	}
	ft_freemat((void **)cmpnts, ft_matlen(cmpnts));
	return ((r << 16) | (g << 8) | b);
}

bool	extract_colors(t_parse *parse, t_data *data)
{
	parse->f_clr = clean_value(&parse->f_clr[1]);
	if (!parse->f_clr)
		return (false);
	parse->c_clr = clean_value(&parse->c_clr[1]);
	if (!parse->c_clr)
		return (false);
	data->txtr->f_clr = convert_color(parse->f_clr);
	if (data->txtr->f_clr == -1)
		return (false);
	data->txtr->c_clr = convert_color(parse->c_clr);
	if (data->txtr->c_clr == -1)
		return (false);
	return (true);
}
