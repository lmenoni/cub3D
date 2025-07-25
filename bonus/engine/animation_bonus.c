/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:32:38 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 13:18:30 by igilani          ###   ########.fr       */
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

t_oimg	*portal_animation(t_txtr *txtr, int n_img, int ipf)
{
	static int i = -1;

	if (n_img <= 0 || !txtr->portal_arr)
		return (NULL);
	i++;
	if (i == (n_img * ipf) - 1)
		i = 0;
	return (&txtr->portal_arr[i / ipf]);
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
