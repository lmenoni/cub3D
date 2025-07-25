/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:28:40 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 17:05:43 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	open_door(t_data *data, t_ray *ray, char **map)
{
	int	x;
	int	y;

	x = (int)floor(ray->p_pos.x + ray->p_dir.x);
	y = (int)floor(ray->p_pos.y + ray->p_dir.y);
	if (map[y][x] == 'D')
	{
		data->hand_status = 1;
		data->hand_timer = 60;
		map[y][x] = 'd';
	}
	else if (map[y][x] == 'd'
		&& map[(int)floor(ray->p_pos.y)][(int)floor(ray->p_pos.x)] != 'd')
	{
		data->hand_status = 2;
		data->hand_timer = 60;
		map[y][x] = 'D';
	}
}

void	hand_open_door(t_data *data, t_txtr *tx)
{
	if (data->hand_status && data->hand_timer > 0)
	{
		data->hand_timer--;
		if (data->hand_timer <= 0)
			data->hand_status = false;
	}
	if (data->hand_status == 0)
		put_image_to_image(data, tx->hand_sword, data->hand_wh
			- tx->hand_sword->width, data->hand_hh - tx->hand_sword->height);
	else if (data->hand_status == 1)
	{
		put_image_to_image(data, tx->right_hand, W_W
			- tx->right_hand->width, W_H - tx->right_hand->height);
		put_image_to_image(data, tx->left_hand, 0, W_H - tx->left_hand->height);
	}
	else if (data->hand_status == 2)
		put_image_to_image(data, tx->right_hand, W_W
			- tx->right_hand->width, W_H - tx->right_hand->height);
}
