/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:55 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/22 20:27:12 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*get_texture_meme(t_data *data)
{
	t_oimg	*isma_arr;
	isma_arr = wall_animation(data->txtr, data->txtr->n_isma, 20000);
	data->txtr->c_clr = 0X000000;//0X110e11
	data->txtr->f_clr = 0X000000;
	return (isma_arr); // NORTH
}

t_oimg	*get_texture(t_data *data)
{
	if (data->map[data->ray->map_y][data->ray->map_x] == 'D')
		return(data->door);
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

void	drawing_loop(t_draw *temp, t_data *data, char *p_addr)
{
	int	y;
	int height_mask;

	y = data->ray->draw_start;
	height_mask = temp->texture->height - 1;
	while (y < data->ray->draw_end)
	{
		temp->tex_y = (int)temp->tex_pos & (height_mask);
		temp->tex_pos += temp->step;
		temp->color = *(int *)(temp->texture->addr
				+ temp->tex_y * temp->texture->l_l
				+ temp->tex_x * (temp->texture->bpp >> 3));
		*(int *)(p_addr + y * data->ximg->l_l) = temp->color;
		y++;
	}
}

void	draw_wall_column(t_data *data, char *p_addr)
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
	drawing_loop(&temp, data, p_addr);
}
