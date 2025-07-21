/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:34 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/18 16:51:45 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	check_for_movement(t_data *data)
{
	if (data->moving)
		move(data, data->ray, data->moving);
	if (data->rotating)
	{
		if (data->rotating == 65361)
			key_rotate(data->ray, -ROT_SPEED);
		if (data->rotating == 65363)
			key_rotate(data->ray, ROT_SPEED);
	}
}

void	set_new_pos(t_vctr *new_pos, t_ray *ray, int keycode)
{
	if (keycode == 119)
	{
		new_pos->x = ray->p_pos.x + (ray->p_dir.x * ray->move_speed);
		new_pos->y = ray->p_pos.y + (ray->p_dir.y * ray->move_speed);
	}
	else if (keycode == 115)
	{
		new_pos->x = ray->p_pos.x - (ray->p_dir.x * ray->move_speed);
		new_pos->y = ray->p_pos.y - (ray->p_dir.y * ray->move_speed);
	}
	else if (keycode == 97)
	{
		new_pos->x = ray->p_pos.x - (ray->plane.x * ray->move_speed);
		new_pos->y = ray->p_pos.y - (ray->plane.y * ray->move_speed);
	}
	else if (keycode == 100)
	{
		new_pos->x = ray->p_pos.x + (ray->plane.x * ray->move_speed);
		new_pos->y = ray->p_pos.y + (ray->plane.y * ray->move_speed);
	}
}

void	move(t_data *data, t_ray *ray, int keycode)
{
	t_vctr	new_pos;
	bool	valid_move_x;
	bool	valid_move_y;
	
	new_pos = (t_vctr){0};
	set_new_pos(&new_pos, ray, keycode);
	valid_move_x = (new_pos.x > 0 && new_pos.x < data->map_w && data->map[(int)floor(ray->p_pos.y)][(int)floor(new_pos.x)] != '1');
	valid_move_y = (new_pos.y > 0 && new_pos.y < data->map_h && data->map[(int)floor(new_pos.y)][(int)floor(ray->p_pos.x)] != '1');
	if (new_pos.x >= data->map_w || new_pos.y >= data->map_h
		|| new_pos.x <= 0 || new_pos.y <= 0
		|| data->map[(int)floor(new_pos.y)][(int)floor(new_pos.x)] == '1')
	{
		if (valid_move_x)
			ray->p_pos.x = new_pos.x;
		if (valid_move_y)
			ray->p_pos.y = new_pos.y;
		return ;
	}
	if (valid_move_x || valid_move_y)
	{
		ray->p_pos.x = new_pos.x;
		ray->p_pos.y = new_pos.y;
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

void	pause_game(t_data *data)
{
	if (!data->pause)
		mlx_mouse_show(data->xdis, data->xwin);
	else
		mlx_mouse_hide(data->xdis, data->xwin);
	data->pause = !data->pause;
}
