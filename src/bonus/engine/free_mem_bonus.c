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

void	free_img_arr(t_oimg *arr, int size, void *xdis)
{
	int		i;
	t_oimg	*t;

	i = 0;
	t = arr;
	if (t)
	{
		while (i < size)
		{
			mlx_destroy_image(xdis, t[i].ptr);
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
	free_utils_images(data->txtr, data->xdis);
	free_door_images(data->txtr, data->xdis);
	free_img_arr(data->txtr->isma_arr, data->txtr->n_isma, data->xdis);
	free_img_arr(data->txtr->portal_arr, data->txtr->n_portal, data->xdis);
	mlx_destroy_display(data->xdis);
	free(data->xdis);
}
