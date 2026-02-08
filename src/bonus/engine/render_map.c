/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:18:32 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 18:18:33 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	render_tile_row(t_data *data, int j, int y, t_oimg *player)
{
	int	i;
	int	x;

	i = (int)data->ray->p_pos.x - 7;
	x = MAP_POS;
	while (i < (int)data->ray->p_pos.x + 7)
	{
		if (i < data->map_w && i >= 0 && j < data->map_h
			&& j >= 0 && (data->map[j][i] == '0' || data->map[j][i] == 'd'))
		{
			if (j == (int)data->ray->p_pos.y && i == (int)data->ray->p_pos.x)
				put_image_to_image(data, player, x, y);
			else
				put_image_to_image(data, data->txtr->empty, x, y);
		}
		i++;
		x += data->txtr->empty->width;
	}
}

void	render_map(t_data *data, t_oimg *player, t_txtr *txtr)
{
	int	y;
	int	j;

	y = MAP_POS;
	j = (int)data->ray->p_pos.y - 7;
	while (j < (int)data->ray->p_pos.y + 7)
	{
		render_tile_row(data, j, y, player);
		j++;
		y += txtr->empty->height;
	}
}

void	map_rendering(t_data *data, t_txtr *txtr)
{
	if (fabs(data->ray->p_dir.x) > fabs(data->ray->p_dir.y))
	{
		if (data->ray->p_dir.x > 0)
			render_map(data, txtr->player_e, txtr);
		else
			render_map(data, txtr->player_w, txtr);
	}
	else
	{
		if (data->ray->p_dir.y > 0)
			render_map(data, txtr->player_s, txtr);
		else
			render_map(data, txtr->player_n, txtr);
	}
}
