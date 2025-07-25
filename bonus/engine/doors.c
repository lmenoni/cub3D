/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:28:40 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 13:53:48 by igilani          ###   ########.fr       */
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
	else if (map[y][x] == 'd' && map[(int)floor(ray->p_pos.y)][(int)floor(ray->p_pos.x)] != 'd')
	{
		data->hand_status = 2;
		data->hand_timer = 60;
		map[y][x] = 'D';
	}
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
