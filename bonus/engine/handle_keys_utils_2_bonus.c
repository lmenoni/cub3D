/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_utils_2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:48:46 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 17:52:48 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	pause_render(t_data *data)
{
	put_image_to_image(data, data->txtr->pause,
		((W_W - data->txtr->pause->width) / 2),
		((W_H - data->txtr->pause->height) / 2));
	mlx_put_image_to_window(data->xdis, data->xwin, data->ximg->ptr, 0, 0);
}

bool	is_valid(t_vctr *pos, t_data *data)
{
	return ((pos->x >= 0 && pos->x < data->map_w
			&& data->map[(int)pos->y][(int)pos->x] != '1'
		&& data->map[(int)pos->y][(int)pos->x] != 'D'));
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
