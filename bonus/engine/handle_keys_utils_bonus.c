/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:34 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/24 00:01:44 by igilani          ###   ########.fr       */
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

bool is_valid(t_vctr *pos, t_data *data)
{
	return ((pos->x >= 0 && pos->x < data->map_w && data->map[(int)pos->y][(int)pos->x] != '1' && data->map[(int)pos->y][(int)pos->x] != 'D'));
}

void	set_new_pos_x(t_data *data, t_vctr *new_pos, t_ray *ray, int keycode)
{
	double	prev;

	prev = new_pos->x;
	if (keycode == 119)
		new_pos->x = ray->p_pos.x + (ray->p_dir.x * ray->move_speed);
	else if (keycode == 115)
		new_pos->x = ray->p_pos.x - (ray->p_dir.x * ray->move_speed);
	else if (keycode == 97)
		new_pos->x = ray->p_pos.x - (ray->plane.x * ray->move_speed);
	else if (keycode == 100)
		new_pos->x = ray->p_pos.x + (ray->plane.x * ray->move_speed);
	if (!is_valid(new_pos, data))
		new_pos->x = prev;
}


void	set_new_pos_y(t_data *data, t_vctr *new_pos, t_ray *ray, int keycode)
{
	double	prev;

	prev = new_pos->y;
	if (keycode == 119)
		new_pos->y = ray->p_pos.y + (ray->p_dir.y * ray->move_speed);
	else if (keycode == 115)
		new_pos->y = ray->p_pos.y - (ray->p_dir.y * ray->move_speed);
	else if (keycode == 97)
		new_pos->y = ray->p_pos.y - (ray->plane.y * ray->move_speed);
	else if (keycode == 100)
		new_pos->y = ray->p_pos.y + (ray->plane.y * ray->move_speed);
	if (!is_valid(new_pos, data))
		new_pos->y = prev;
}

void	move(t_data *data, t_ray *ray, int keycode)
{
	t_vctr	new_pos;
	
	new_pos = (t_vctr){0};
	new_pos.y = ray->p_pos.y;
	new_pos.x = ray->p_pos.x;
	
	set_new_pos_x(data, &new_pos, ray, keycode);
	set_new_pos_y(data, &new_pos, ray, keycode);
	hand_animation(data, ray, &new_pos);
	ray->p_pos.x = new_pos.x;
	ray->p_pos.y = new_pos.y;
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
	ray->move_speed = MOV_SPEED;
}

void	pause_game(t_data *data)
{
	if (!data->pause)
		mlx_mouse_show(data->xdis, data->xwin);
	else
		mlx_mouse_hide(data->xdis, data->xwin);
	data->pause = !data->pause;
}
