/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:28:40 by igilani           #+#    #+#             */
/*   Updated: 2025/07/24 13:21:26 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	open_door(t_data *data, t_ray *ray, char **map)
{
	int	x;
	int	y;

	x = (int)floor(ray->p_pos.x + ray->p_dir.x);
	y = (int)floor(ray->p_pos.y + ray->p_dir.y);
	if (map[y][x] == 'D' && data->door_animation_state == 0)
	{
		data->hand_status = 1;
		data->hand_timer = 60;
		data->door_animation_state = 1;
		data->door_animation_frame = 0;
		data->door_animation_timer = 0;
		data->door_pos_x = x;
		data->door_pos_y = y;
	}
	else if (map[y][x] == 'd' && data->door_animation_state == 0)
	{
		data->hand_status = 2;
		data->hand_timer = 60;
		data->door_animation_state = 2;
		data->door_animation_frame = 15;
		data->door_animation_timer = 0;
		data->door_pos_x = x;
		data->door_pos_y = y;
	}
}

void	update_door_animation(t_data *data)
{
	if (data->door_animation_state == 0)
		return ;
	
	data->door_animation_timer++;
	if (data->door_animation_timer >= 5)
	{
		data->door_animation_timer = 0;
		
		if (data->door_animation_state == 1)
		{
			data->door_animation_frame++;
			if (data->door_animation_frame >= 16)
			{
				data->door_animation_frame = 15;
				data->door_animation_state = 0;
				if (data->door_pos_x >= 0 && data->door_pos_y >= 0)
					data->map[data->door_pos_y][data->door_pos_x] = 'd';
				data->door_pos_x = -1;
				data->door_pos_y = -1;
			}
		}
		else if (data->door_animation_state == 2)
		{
			data->door_animation_frame--;
			if (data->door_animation_frame < 0)
			{
				data->door_animation_frame = 0;
				data->door_animation_state = 0;
				if (data->door_pos_x >= 0 && data->door_pos_y >= 0)
					data->map[data->door_pos_y][data->door_pos_x] = 'D';
				data->door_pos_x = -1;
				data->door_pos_y = -1;
			}
		}
	}
}

t_oimg	*get_door_frame(t_data *data)
{
	if (!data->txtr->door_arr)
		return (NULL);
	return (&data->txtr->door_arr[data->door_animation_frame]);
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