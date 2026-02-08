/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:55 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 17:37:24 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*get_door_texture(t_data *data, t_ray *ray, int side, t_vctr map)
{
	if (data->map[(int)map.y][(int)map.x] == 'D')
		return (data->txtr->door);
	if (side == 0)
	{
		if (ray->ray_dir.x > 0 && data->map[ray->map_y][ray->map_x - 1] == 'd')
			return (data->txtr->e_door);
		else if (data->map[ray->map_y][ray->map_x + 1] == 'd')
			return (data->txtr->w_door);
	}
	else if (side == 1)
	{
		if (ray->ray_dir.y > 0 && data->map[ray->map_y - 1][ray->map_x] == 'd')
			return (data->txtr->s_door);
		else if (ray->map_y + 1 < data->map_h
			&& data->map[ray->map_y + 1][ray->map_x] == 'd')
			return (data->txtr->n_door);
	}
	return (NULL);
}

t_oimg	*get_texture(t_data *data, t_ray *ray, int side, t_vctr map)
{
	if (get_door_texture(data, ray, side, map))
		return (get_door_texture(data, ray, side, map));
	if (side == 0)
	{
		if (ray->ray_dir.x > 0)
			return (data->txtr->e_img);
		return (data->txtr->w_img);
	}
	if (ray->ray_dir.y > 0)
		return (data->txtr->s_img);
	return (data->txtr->n_img);
}

int	get_texture_x_coordinate(t_draw *temp, t_data *data, double dist, int side)
{
	double	wall_x;
	int		tex_x;

	wall_x = 0;
	tex_x = 0;
	if (side == 0)
		wall_x = data->ray->p_pos.y + dist
			* data->ray->ray_dir.y;
	else
		wall_x = data->ray->p_pos.x + dist
			* data->ray->ray_dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)temp->texture->width);
	if (side == 0 && data->ray->ray_dir.x > 0)
		tex_x = temp->texture->width - tex_x - 1;
	if (side == 1 && data->ray->ray_dir.y < 0)
		tex_x = temp->texture->width - tex_x - 1;
	return (tex_x);
}

void	drawing_loop(t_draw *temp, t_data *data, char *p_addr)
{
	int	y;
	int	height_mask;

	y = data->ray->draw_start;
	height_mask = temp->texture->height - 1;
	while (y < data->ray->draw_end)
	{
		temp->tex_y = (int)temp->tex_pos & (height_mask);
		temp->tex_pos += temp->step;
		temp->color = *(int *)(temp->texture->addr
				+ temp->tex_y * temp->texture->l_l
				+ temp->tex_x * (temp->texture->bpp >> 3));
		if (temp->color != 0x75ff75)
		{
			if (data->map[data->ray->map_y][data->ray->map_x] == 'd'
				&& ISMA == 1)
				temp->color = convert_purple_to_green(temp->color);
			*(int *)(p_addr + y * data->ximg->l_l) = temp->color;
		}
		y++;
	}
}

void	draw_wall_column(t_data *data, char *p_addr, bool is_door)
{
	t_draw	temp;

	temp = (t_draw){0};
	if ((is_door && data->ray->side_door == -1) || data->ray->side == -1)
		return ;
	if (ISMA == 1)
		temp.texture = get_texture_meme(data,
				(t_vctr){data->ray->map_x, data->ray->map_y});
	else
		temp.texture = get_texture(data, data->ray, data->ray->side,
				(t_vctr){data->ray->map_x, data->ray->map_y});
	temp.tex_x = get_texture_x_coordinate(&temp, data,
			data->ray->perp_dist, data->ray->side);
	temp.step = 1.0 * temp.texture->height / data->ray->draw_len;
	temp.tex_pos = (data->ray->draw_start - W_H / 2
			+ data->ray->draw_len / 2) * temp.step;
	drawing_loop(&temp, data, p_addr);
}
