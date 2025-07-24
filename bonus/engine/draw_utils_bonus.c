/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:31:22 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/24 15:51:48 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

// void	my_pixel_put(int x, int y, t_data *data, int color)
// {
// 	if (color != 0x75ff75)
// 		*((unsigned int *)(data->ximg->addr + y * data->ximg->l_l + x * (data->ximg->bpp >> 3))) = color;
// }

void	compute_projection(t_data *data, double perp_dist)
{
	if (perp_dist == 0)
	{
		data->ray->draw_len = data->ximg->height;
		data->ray->draw_start = W_H / 2;
		data->ray->draw_end = W_H / 2;
		return ;
	}
	data->ray->draw_len = (int)(data->ximg->height / perp_dist);
	data->ray->draw_start = (-data->ray->draw_len / 2)
		+ (data->ximg->height / 2);
	if (data->ray->draw_start < 0)
		data->ray->draw_start = 0;
	data->ray->draw_end = (data->ray->draw_len / 2) + (data->ximg->height / 2);
	if (data->ray->draw_end >= data->ximg->height)
		data->ray->draw_end = data->ximg->height - 1;
}

void	draw_remaining_background(t_data *data, char *p_addr)
{
	int y;

	y = 0;
	while (y < data->ray->draw_start)
	{
		*((unsigned int *)(p_addr + (y * data->ximg->l_l))) = data->txtr->c_clr;
		y++;
	}
	y = data->ray->draw_end;
	while (y < data->ximg->height)
	{
		*((unsigned int *)(p_addr + (y * data->ximg->l_l))) = data->txtr->f_clr;
		y++;
	}
}