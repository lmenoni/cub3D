/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:31:22 by lmenoni           #+#    #+#             */
/*   Updated: 2025/08/04 15:02:52 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	get_in_color(t_oimg *in, int j, int i)
{
	return (*(unsigned int *)(in->addr
		+ (j * in->l_l)
		+ (i * (in->bpp >> 3))));
}

void	put_image_to_image(t_data *data, t_oimg *in, int x, int y)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	j = 0;
	color = 0;
	while (j < in->height)
	{
		i = 0;
		while (i < in->width)
		{
			if ((x + i) >= 0 && (x + i) < data->ximg->width
				&& (y + j) >= 0 && (y + j) < data->ximg->height)
			{
				color = get_in_color(in, j, i);
				if (color != 0x75ff75)
					*((unsigned int *)(data->ximg->addr
						+ (y + j) * data->ximg->l_l
						+ (x + i) * (data->ximg->bpp >> 3))) = color;
			}
			i++;
		}
		j++;
	}
}

t_oimg	*get_texture_meme(t_data *data, t_vctr map)
{
	t_oimg	*isma_arr;
	t_oimg	*portal_arr;

	isma_arr = wall_animation(data->txtr, data->txtr->n_isma, 20000);
	portal_arr = portal_animation(data->txtr, data->txtr->n_portal, 20000);
	data->txtr->c_clr = 0X000000;
	data->txtr->f_clr = 0X000000;
	if (data->map[(int)map.y][(int)map.x] == 'D'
		|| (data->map[(int)map.y][(int)map.x] == 'd' && ISMA == 1))
		return (portal_arr);
	return (isma_arr);
}

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
	int	y;

	if (data->ray->draw_start < 0 || data->ray->draw_start > data->ximg->height)
		return ;
	if (data->ray->draw_end < 0 || data->ray->draw_end > data->ximg->height)
		return ;
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
