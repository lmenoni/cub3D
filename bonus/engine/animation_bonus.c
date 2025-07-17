/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:32:38 by igilani           #+#    #+#             */
/*   Updated: 2025/07/17 19:10:27 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*wall_animation(t_data *data, t_txtr *txtr, int n_img)
{
	static int i = -1;

	(void)data;
	if (n_img <= 0 || !txtr->isma_arr)
		return (NULL);
	
	// static int current_frame;
	// static int frame_count;
	// int frame_interval;

	// current_frame = 0;
	// frame_count = 0;
	// frame_interval = 10;

	// if (n_img <= 0 || !txtr->isma_arr)
	// 	return ;
	// frame_count++;
	// if (frame_count >= frame_interval)
	// {
	// 	frame_count = 0;
	// 	current_frame++;
	// 	if (current_frame > n_img)
	// 		current_frame = 0;
	// }
	i++;
	if (i == (n_img * 20000) - 1)
		i = 0;
	return (&txtr->isma_arr[i / 20000]);
	// mlx_put_image_to_window(data->xdis, data->xwin,
	// 	txtr->isma_arr[i / 20].ptr, W_W - txtr->isma_arr[i / 20].width, W_H - txtr->isma_arr[i / 20].height);
}