/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:55 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 17:59:31 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_oimg	*get_texture(t_data *data)
{
	if (data->ray->side == 0)
	{
		if (data->ray->ray_dir.x > 0)
			return (data->txtr->w_img);
		return (data->txtr->e_img);
	}
	if (data->ray->ray_dir.y > 0)
		return (data->txtr->n_img);
	return (data->txtr->s_img);
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
	int	offset;

	y = 0;
	y = data->ray->draw_start;
	offset = 0;
	while (y < data->ray->draw_end)
	{
		temp->tex_y = (int)temp->tex_pos & (temp->texture->height - 1);
		temp->tex_pos += temp->step;
		temp->color = *(int *)(temp->texture->addr
				+ temp->tex_y * temp->texture->l_l
				+ temp->tex_x * (temp->texture->bpp / 8));
		offset = (y * data->ximg->l_l) + (x * (data->ximg->bpp / 8));
		*((unsigned int *)(data->ximg->addr + offset)) = temp->color;
		y++;
	}
}

void	draw_wall_column(t_data *data, int x)
{
	t_draw	temp;

	temp = (t_draw){0};
	if (data->ray->side == -1)
		return ;
	temp.texture = get_texture(data);
	temp.tex_x = get_texture_x_coordinate(&temp, data);
	temp.step = 1.0 * temp.texture->height / data->ray->draw_len;
	temp.tex_pos = (data->ray->draw_start - W_H / 2
			+ data->ray->draw_len / 2) * temp.step;
	drawing_loop(&temp, data, x);
}
