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

#include "../cub3D.h"

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
	if (keycode == 45 && data->ray->move_speed > 0.05)
		data->ray->move_speed -= MOV_SPEED;
	if (keycode == 114)
		reset(data->ray);
	if (keycode == 65361 || keycode == 65363)
		data->rotating = keycode;
	return (0);
}
