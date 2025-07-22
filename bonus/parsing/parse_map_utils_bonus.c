/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:18:09 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:18:11 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	multiple_start(char c)
{
	static bool	start;

	if (ft_strchr("NSWE", c))
	{
		if (start)
			return (true);
		else
			start = true;
	}
	return (false);
}

bool	invalid_char(char *s, t_data *data)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = 0;
	while (s[i])
	{
		if (multiple_start(s[i]))
			return (ft_printf_fd(2, MAP_MSTART), true);
		if (!ft_strchr(CHR_OK, s[i]))
			return (ft_printf_fd(2, MAP_INV), true);
		if (s[i] != '\n' && s[i] != '\r')
			line_len++;
		i++;
	}
	if (data->map_w < line_len)
		data->map_w = line_len;
	return (false);
}

void	copy_row(char *r, char *s, int y, t_parse *parse)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n' && s[i] != '\r')
	{
		if (ft_strchr("NSEW", s[i]))
		{
			parse->facing = s[i];
			parse->p_x = i + 0.5;
			parse->p_y = y + 0.5;
			r[i] = '0';
		}
		else if (!is_space(s[i]))
			r[i] = s[i];
		i++;
	}
}

bool	bool_fill(char **map, t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map_h || x < 0 || x >= data->map_w)
		return (false);
	if (map[y][x] != '0' && map[y][x] != 'D')
		return (true);
	map[y][x] = 'V';
	return (bool_fill(map, data, y + 1, x)
		&& bool_fill(map, data, y - 1, x)
		&& bool_fill(map, data, y, x + 1)
		&& bool_fill(map, data, y, x - 1));
}

void	clean_up(t_data *data, char **temp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] && temp[i])
	{
		j = 0;
		while (data->map[i][j] && temp[i][j])
		{
			if (temp[i][j] == '0')
				data->map[i][j] = ' ';
			j++;
		}
		i++;
	}
}
