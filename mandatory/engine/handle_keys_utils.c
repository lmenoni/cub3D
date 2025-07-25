/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:34 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 18:03:24 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_for_movement(t_data *data)
{
	if (data->moving)
		move(data->ray, data->moving);
	if (data->rotating)
	{
		if (data->rotating == 65361)
			key_rotate(data->ray, -ROT_SPEED);
		if (data->rotating == 65363)
			key_rotate(data->ray, ROT_SPEED);
	}
}

void	move(t_ray *ray, int keycode)
{
	if (keycode == 119)
	{
		ray->p_pos.x += ray->p_dir.x * ray->move_speed;
		ray->p_pos.y += ray->p_dir.y * ray->move_speed;
	}
	else if (keycode == 115)
	{
		ray->p_pos.x -= ray->p_dir.x * ray->move_speed;
		ray->p_pos.y -= ray->p_dir.y * ray->move_speed;
	}
	else if (keycode == 97)
	{
		ray->p_pos.x -= ray->plane.x * ray->move_speed;
		ray->p_pos.y -= ray->plane.y * ray->move_speed;
	}
	else if (keycode == 100)
	{
		ray->p_pos.x += ray->plane.x * ray->move_speed;
		ray->p_pos.y += ray->plane.y * ray->move_speed;
	}
}

void	key_rotate(t_ray *ray, double rot)
{
	double	old_dir;
	double	old_plane;

	old_dir = ray->p_dir.x;
	old_plane = ray->plane.x;
	ray->p_dir.x = ray->p_dir.x * cos(rot) - ray->p_dir.y * sin(rot);
	ray->p_dir.y = old_dir * sin(rot) + ray->p_dir.y * cos(rot);
	ray->plane.x = ray->plane.x * cos(rot) - ray->plane.y * sin(rot);
	ray->plane.y = old_plane * sin(rot) + ray->plane.y * cos(rot);
}

void	reset(t_ray *ray)
{
	ray->p_pos.x = ray->p_pos_ori.x;
	ray->p_pos.y = ray->p_pos_ori.y;
	ray->p_dir.x = ray->p_dir_ori.x;
	ray->p_dir.y = ray->p_dir_ori.y;
	ray->plane.x = ray->plane_ori.x;
	ray->plane.y = ray->plane_ori.y;
}
