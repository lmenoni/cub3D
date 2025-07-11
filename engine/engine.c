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

void	prepare_ray(t_ray *ray, int x)
{
	//calcolo camera
	ray->cam_len = 2.0 * x / W_W - 1.0;	
	//calcolo direzione del raggio
	ray->ray_dir.x = ray->p_dir->x + ray->plane->x * ray->cam_len;
	ray->ray_dir.y = ray->p_dir->y + ray->plane->y * ray->cam_len;
	//calcolo della posizione sulla griglia
	ray->map_x = (int)ray->p_pos->x;
	ray->map_y = (int)ray->p_pos->y;
	//calcolo della delta distanza
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	//calcolo delle step e delle side distance iniziali
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (ray->p_pos->x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - ray->p_pos->x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (ray->p_pos->y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - ray->p_pos->y) * ray->delta_dist.y;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int hit;
	
	hit = 0;
	while(hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x >= data->map_w || ray->map_x < 0 ||
			ray->map_y >= data->map_h || ray->map_y < 0)
		{
			hit = 1;
			ray->perp_dist = 999999;
		}
		else if (data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - ray->p_pos->x + (1 - ray->step_x) / 2) / ray->ray_dir.x;
	else
		ray->perp_dist = (ray->map_y - ray->p_pos->y + (1 - ray->step_y) / 2) / ray->ray_dir.y;	
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
	int x;

	x = 0;
	set_background(data);
	cast_rays(data);
	return (0);
}