/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:18:25 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:18:27 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	**normalize_map(char **map, t_data *data, t_parse *parse)
{
	char	**r;
	int		i;

	i = 0;
	r = NULL;
	r = malloc((data->map_h + 1) * sizeof(char *));
	if (!r)
		return (ft_printf_fd(2, E_ALLOC), NULL);
	while (i < data->map_h)
	{
		r[i] = malloc((data->map_w + 1) * sizeof(char));
		if (!r[i])
		{
			ft_freemat((void **)r, ft_matlen(r));
			return (ft_printf_fd(2, E_ALLOC), NULL);
		}
		r[i] = (char *)ft_memset((void *)r[i], '0', data->map_w);
		r[i][data->map_w] = '\0';
		copy_row(r[i], map[i], i, parse);
		i++;
	}
	r[i] = NULL;
	return (r);
}

bool	check_characters(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (is_empty(map[i]))
		{
			data->map = NULL;
			return (ft_printf_fd(2, MAP_EMPTY), false);
		}
		if (invalid_char(map[i], data))
		{
			data->map = NULL;
			return (false);
		}
		i++;
	}
	data->map_h = i;
	return (true);
}

bool	incased(char **map, t_data *data, t_parse *parse)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!bool_fill(map, data, parse->p_y, parse->p_x))
		return (false);
	clean_up(data);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'V')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
	return (true);
}

bool	parse_map(char **map, t_data *data, t_parse *parse)
{
	if (!map)
		return (ft_printf_fd(2, MAP_NULL), false);
	if (!check_characters(map, data))
		return (false);
	data->map = normalize_map(map, data, parse);
	if (parse->facing == '\0')
		return (ft_printf_fd(2, MAP_NSTART), false);
	if (!incased(data->map, data, parse))
		return (ft_printf_fd(2, MAP_INC), false);
	return (true);
}
