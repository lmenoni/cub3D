/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:31:04 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/16 16:34:10 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	free_images(t_data *data)
{
	if (data->ximg)
	{
		mlx_destroy_image(data->xdis, data->ximg->ptr);
		free(data->ximg);
	}
	if (data->txtr->n_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->n_img->ptr);
		free(data->txtr->n_img);
	}
	if (data->txtr->s_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->s_img->ptr);
		free(data->txtr->s_img);
	}
	if (data->txtr->e_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->e_img->ptr);
		free(data->txtr->e_img);
	}
	if (data->txtr->w_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->w_img->ptr);
		free(data->txtr->w_img);
	}
}

void	free_minimap(t_data *data)
{
	if (data->txtr->player_n)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_n->ptr);
		free(data->txtr->player_n);
	}
	if (data->txtr->player_s)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_s->ptr);
		free(data->txtr->player_s);
	}
	if (data->txtr->player_e)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_e->ptr);
		free(data->txtr->player_e);
	}
	if (data->txtr->player_w)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_w->ptr);
		free(data->txtr->player_w);
	}
	if (data->txtr->empty)
	{
		mlx_destroy_image(data->xdis, data->txtr->empty->ptr);
		free(data->txtr->empty);
	}
}

void	free_isma_arr(t_data *data)
{
	int		i;
	t_oimg	*t;

	i = 0;
	t = data->txtr->isma_arr;
	if (t)
	{
		while (i < data->txtr->n_isma)
		{
			mlx_destroy_image(data->xdis, t[i].ptr);
			i++;
		}
		free(t);
	}
}

void	free_data(t_data *data)
{
	if (data->file)
		ft_freemat((void **)data->file, ft_matlen(data->file));
	if (data->map)
		ft_freemat((void **)data->map, ft_matlen(data->map));
	if (data->xwin)
		mlx_destroy_window(data->xdis, data->xwin);
	free_images(data);
	free_minimap(data);
	free_isma_arr(data);
	mlx_destroy_display(data->xdis);
	free(data->xdis);
}
