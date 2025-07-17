/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:55 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/17 19:25:22 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*get_texture_meme(t_data *data)
{
	if (data->ray->side == 0) // Colpito muro verticale (est-ovest)
	{
		if (data->ray->ray_dir.x > 0)
			return (data->txtr->e_img); // EAST
		return (data->txtr->w_img); // WEST
	}
	if (data->ray->ray_dir.y > 0)
		return (data->txtr->s_img); // SOUTH
	return (wall_animation(data, data->txtr, data->txtr->n_isma)); // NORTH
}

t_oimg	*get_texture(t_data *data)
{
	if (data->ray->side == 0) // Colpito muro verticale (est-ovest)
	{
		if (data->ray->ray_dir.x > 0)
			return (data->txtr->e_img); // EAST
		return (data->txtr->w_img); // WEST
	}
	if (data->ray->ray_dir.y > 0)
		return (data->txtr->s_img); // SOUTH
	return (data->txtr->n_img); // NORTH
}

int	get_texture_x_coordinate(t_draw *temp, t_data *data)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0;
	tex_x = 0;
	if (data->ray->side == 0)
		wall_x = data->ray->p_pos.y + data->ray->perp_dist
			* data->ray->ray_dir.y;
	else
		wall_x = data->ray->p_pos.x + data->ray->perp_dist
			* data->ray->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)temp->texture->width);
	if (data->ray->side == 0 && data->ray->ray_dir.x > 0)
		tex_x = temp->texture->width - tex_x - 1;
	if (data->ray->side == 1 && data->ray->ray_dir.y < 0)
		tex_x = temp->texture->width - tex_x - 1;
	return (tex_x);
}

void	drawing_loop(t_draw *temp, t_data *data, int x)
{
	int	y;

	y = 0;
	y = data->ray->draw_start;
	
	while (y < data->ray->draw_end)
	{
		temp->tex_y = (int)temp->tex_pos & (temp->texture->height - 1);
		temp->tex_pos += temp->step;
		temp->color = *(int *)(temp->texture->addr
				+ temp->tex_y * temp->texture->l_l
				+ temp->tex_x * (temp->texture->bpp / 8));
		my_pixel_put(x, y, data, temp->color);
		y++;
	}
}

void	draw_wall_column(t_data *data, int x)
{
	t_draw	temp;

	temp = (t_draw){0};
	if (data->ray->side == -1)
		return ;
	if (ISMA == 1)
		temp.texture = get_texture_meme(data);
	else
		temp.texture = get_texture(data);
	temp.tex_x = get_texture_x_coordinate(&temp, data);
	temp.step = 1.0 * temp.texture->height / data->ray->draw_len;
	temp.tex_pos = (data->ray->draw_start - W_H / 2
			+ data->ray->draw_len / 2) * temp.step;
	drawing_loop(&temp, data, x);
}
