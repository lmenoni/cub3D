/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:30:27 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:30:28 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	close_window(t_data *data)
{
	free_data(data);
	exit(0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == 119 || keycode == 115
		|| keycode == 97 || keycode == 100)
		data->moving = 0;
	if (keycode == 65361 || keycode == 65363)
		data->rotating = 0;
	return (0);
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	if (keycode == 119 || keycode == 115
		|| keycode == 97 || keycode == 100)
		data->moving = keycode;
	if (keycode == 61)
		data->ray->move_speed += MOV_SPEED;
	if (keycode == 45)
	{
		if (data->ray->move_speed > MOV_SPEED)
			data->ray->move_speed -= MOV_SPEED;
		else
			data->ray->move_speed = 0.0;
	}
	if (keycode == 114)
		reset(data->ray);
	if (keycode == 105)
		data->show_menu = !data->show_menu;
	if (keycode == 112)
		pause_game(data);
	if (keycode == 65361 || keycode == 65363)
		data->rotating = keycode;
	if (keycode == 101)
		open_door(data, data->ray, data->map);
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	static int	prev_x = -1;
	int			delta_x;
	double		rot_speed;

	(void)y;
	if (!data->pause)
	{
		if (prev_x == -1)
			prev_x = x;
		delta_x = x - prev_x;
		prev_x = x;
		if (delta_x == 0)
			return (0);
		rot_speed = delta_x * 0.001;
		if (x <= 250 || x >= W_W - 250 || y <= 250 || y >= W_H - 250)
		{
			mlx_mouse_move(data->xdis, data->xwin, W_W / 2, W_H / 2);
			prev_x = W_W / 2;
			return (0);
		}
		key_rotate(data->ray, rot_speed);
	}
	return (0);
}
