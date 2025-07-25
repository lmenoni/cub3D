/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:32:38 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 16:59:54 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*wall_animation(t_txtr *txtr, int n_img, int ipf)
{
	static int	i = -1;

	if (n_img <= 0 || !txtr->isma_arr)
		return (NULL);
	i++;
	if (i == (n_img * ipf) - 1)
		i = 0;
	return (&txtr->isma_arr[i / ipf]);
}

t_oimg	*portal_animation(t_txtr *txtr, int n_img, int ipf)
{
	static int	i = -1;

	if (n_img <= 0 || !txtr->portal_arr)
		return (NULL);
	i++;
	if (i == (n_img * ipf) - 1)
		i = 0;
	return (&txtr->portal_arr[i / ipf]);
}

void	hand_animation(t_data *data, t_ray *ray, t_vctr *new_pos)
{
	float	bob_offset;
	int		diff;

	if (new_pos->x != ray->p_pos.x || new_pos->y != ray->p_pos.y)
	{
		data->walk_anim_time += 0.1f;
		bob_offset = sin(data->walk_anim_time) * 15.0f;
		data->hand_hh = W_H + (int)bob_offset;
		data->hand_wh = W_W + (int)(cos(data->walk_anim_time * 0.5f) * 5.0f);
	}
	else
	{
		if (data->hand_hh != W_H)
		{
			diff = W_H - data->hand_hh;
			data->hand_hh += diff * 0.1f;
		}
		if (data->hand_wh != W_W)
		{
			diff = W_W - data->hand_wh;
			data->hand_wh += diff * 0.1f;
		}
	}
}
