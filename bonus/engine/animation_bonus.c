/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:32:38 by igilani           #+#    #+#             */
/*   Updated: 2025/07/23 19:09:04 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*wall_animation(t_txtr *txtr, int n_img, int ipf)
{
	static int i = -1;

	if (n_img <= 0 || !txtr->isma_arr)
		return (NULL);
	i++;
	if (i == (n_img * ipf) - 1)
		i = 0;
	return (&txtr->isma_arr[i / ipf]);
}

void hand_open_door(t_data *data)
{
	if (data->hand_status && data->hand_timer > 0)
	{
		data->hand_timer--;
		if (data->hand_timer <= 0)
			data->hand_status = false;
	}
	if (data->hand_status == 0)
		put_image_to_image(data, data->hand_sword, data->hand_width - data->hand_sword->width, data->hand_height - data->hand_sword->height);
	else if (data->hand_status == 1)
	{
		put_image_to_image(data, data->right_hand, W_W - data->right_hand->width, W_H - data->right_hand->height);
		put_image_to_image(data, data->left_hand, 0, W_H - data->left_hand->height);
	}
	else if (data->hand_status == 2)
		put_image_to_image(data, data->right_hand, W_W - data->right_hand->width, W_H - data->right_hand->height);
}

void	hand_animation(t_data *data, t_ray *ray, t_vctr *new_pos)
{
	if (new_pos->x != ray->p_pos.x || new_pos->y != ray->p_pos.y)
	{
		data->walk_animation_time += 0.1f;
		float bob_offset = sin(data->walk_animation_time) * 15.0f;
		data->hand_height = W_H + (int)bob_offset;
		data->hand_width = W_W + (int)(cos(data->walk_animation_time * 0.5f) * 5.0f);
	}
	else
	{
		if (data->hand_height != W_H)
		{
			int diff = W_H - data->hand_height;
			data->hand_height += diff * 0.1f;
		}
		if (data->hand_width != W_W)
		{
			int diff = W_W - data->hand_width;
			data->hand_width += diff * 0.1f;
		}
	}
}
