/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:21:21 by igilani           #+#    #+#             */
/*   Updated: 2025/07/11 20:37:17 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	my_pixel_put(int x, int y, t_data *data, int color)
{
	int	offset;

	offset = (y * data->ximg->l_l) + (x * (data->ximg->bpp / 8));
	*((unsigned int *)(data->ximg->addr + offset)) = color;
}

void	set_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->ximg->height)
	{
		x = 0;
		while (x < data->ximg->width)
		{
			if (y < data->ximg->height / 2)
				my_pixel_put(x, y, data, data->txtr->c_clr);
			else if (y >= data->ximg->height / 2)
				my_pixel_put(x, y, data, data->txtr->f_clr);
			x++;
		}
		y++;
	}
}

void	compute_projection(t_data *data)
{
	int l_l;
	
	l_l = (int)(data->ximg->height / data->ray->perp_dist);
	data->ray->draw_start = (-l_l / 2) + (data->ximg->height / 2);
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0;
	data->ray->draw_end = (l_l / 2) + (data->ximg->height / 2);
	if (data->ray->draw_end >= data->ximg->height)
		data->ray->draw_end = data->ximg->height - 1;
}

void	draw_wall_column(t_data *data, int x)
{
	int y;
	int color;

	if (data->ray->side == -1)
		return ;
	if (data->ray->side == 0) // Colpito muro verticale (est-ovest)
	{
		if (data->ray->ray_dir.x > 0)
			color = 0xFF0000; // Rosso per WEST
		else
			color = 0x0000FF; // Blu per EAST
	}
	else // Colpito muro orizzontale (nord-sud)
	{
		if (data->ray->ray_dir.y > 0)
			color = 0x00FF00; // Verde per NORTH
		else
			color = 0xFFFF00; // Giallo per SOUTH
	}
	y = data->ray->draw_start;
	while (y < data->ray->draw_end)
	{
		my_pixel_put(x, y, data, color);
		y++;
	}
}

void	cast_rays(t_data *data)
{
	int x;

	x = 0;
	while (x < W_W)
	{
		prepare_ray(data->ray, x);
		perform_dda(data, data->ray);
		compute_projection(data);
		draw_wall_column(data, x);
		x++;
	}
	mlx_put_image_to_window(data->xdis, data->xwin, data->ximg->ptr, 0, 0);
}

int	engine_render(t_data *data)
{
	set_background(data);
	cast_rays(data);
	return (0);
}