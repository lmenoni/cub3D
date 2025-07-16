/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:31:04 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:31:06 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

void	free_data(t_data *data)
{
	if (data->file)
		ft_freemat((void **)data->file, ft_matlen(data->file));
	if (data->map)
		ft_freemat((void **)data->map, ft_matlen(data->map));
	if (data->xwin)
		mlx_destroy_window(data->xdis, data->xwin);
	free_images(data);
	mlx_destroy_display(data->xdis);
	free(data->xdis);
}
