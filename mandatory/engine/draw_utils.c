/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:31:22 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 18:02:57 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_pixel_put(int x, int y, t_data *data, int color)
{
	int	offset;

	offset = (y * data->ximg->l_l) + (x * (data->ximg->bpp / 8));
	*((unsigned int *)(data->ximg->addr + offset)) = color;
}

void	compute_projection(t_data *data)
{
	if (data->ray->perp_dist == 0)
	{
		data->ray->draw_len = data->ximg->height;
		data->ray->draw_start = W_H / 2;
		data->ray->draw_end = W_H / 2;
		return ;
	}
	data->ray->draw_len = (int)(data->ximg->height / data->ray->perp_dist);
	data->ray->draw_start = (-data->ray->draw_len / 2)
		+ (data->ximg->height / 2);
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0;
	data->ray->draw_end = (data->ray->draw_len / 2) + (data->ximg->height / 2);
	if (data->ray->draw_end >= data->ximg->height)
		data->ray->draw_end = data->ximg->height - 1;
}

void	set_background(t_data *data)
{
	int	x;
	int	y;
	int	offset;

	y = 0;
	offset = 0;
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
