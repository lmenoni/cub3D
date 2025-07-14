/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:21:21 by igilani           #+#    #+#             */
/*   Updated: 2025/07/14 13:53:41 by igilani          ###   ########.fr       */
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
	data->ray->draw_len = (int)(data->ximg->height / data->ray->perp_dist);
	data->ray->draw_start = (-data->ray->draw_len / 2) + (data->ximg->height / 2);
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0;
	data->ray->draw_end = (data->ray->draw_len / 2) + (data->ximg->height / 2);
	if (data->ray->draw_end >= data->ximg->height)
		data->ray->draw_end = data->ximg->height - 1;
}

t_oimg	*get_texture(t_data *data)
{
	if (data->ray->side == 0) // Colpito muro verticale (est-ovest)
	{
		if (data->ray->ray_dir.x > 0)
			return (data->txtr->w_img);// WEST
		return (data->txtr->e_img); // EAST
	}
	if (data->ray->ray_dir.y > 0)
			return (data->txtr->n_img); // NORTH
	return (data->txtr->s_img); // SOUTH
}

void	draw_wall_column(t_data *data, int x)
{
	int y;
	t_oimg	*texture;
	double wallX;
	int texX;
	int texY;
	double step;
	double texPos;
	
	int color;

	y = 0;
	color = 0;
	texture = NULL;
	wallX = 0;
	texY = 0;
	texX = 0;
	step = 0;
	if (data->ray->side == -1)
		return ;
	texture = get_texture(data);
	if (data->ray->side == 0)
		wallX = data->ray->p_pos.y + data->ray->perp_dist * data->ray->ray_dir.y;
	else
		wallX = data->ray->p_pos.x + data->ray->perp_dist * data->ray->ray_dir.x;
	wallX -= floor(wallX);

	// Calcola texX
	texX = (int)(wallX * (double)texture->width);
	if (data->ray->side == 0 && data->ray->ray_dir.x > 0)
		texX = texture->width - texX - 1;
	if (data->ray->side == 1 && data->ray->ray_dir.y < 0)
		texX = texture->width - texX - 1;

	// Calcola step e posizione iniziale nella texture
	step = 1.0 * texture->height / data->ray->draw_len;
	texPos = (data->ray->draw_start - W_H / 2 + data->ray->draw_len / 2) * step;

	// Disegna la colonna pixel per pixel
	y = data->ray->draw_start;
	while (y < data->ray->draw_end)
	{
		texY = (int)texPos & (texture->height - 1);
		texPos += step;

		// Preleva il colore dalla texture
		color = *(int *)(texture->addr + texY * texture->l_l + texX * (texture->bpp / 8));

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