/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:19:15 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 17:43:36 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	init_data(t_data *data)
{
	data->hand_status = 0;
	data->hand_timer = 0;
	data->hand_wh = W_W;
	data->hand_hh = W_H;
	data->walk_anim_time = 0.0f;
	data->xdis = mlx_init();
}

void	get_dir_vector(char face, t_ray *ray)
{
	if (face == 'N')
	{
		ray->p_dir.x = 0;
		ray->p_dir.y = -1;
	}
	else if (face == 'S')
	{
		ray->p_dir.x = 0;
		ray->p_dir.y = 1;
	}
	else if (face == 'E')
	{
		ray->p_dir.x = 1;
		ray->p_dir.y = 0;
	}
	else if (face == 'W')
	{
		ray->p_dir.x = -1;
		ray->p_dir.y = 0;
	}
}

bool	get_vector(t_parse *parse, t_ray *ray)
{
	ray->p_pos = (t_vctr){0};
	ray->p_dir = (t_vctr){0};
	ray->plane = (t_vctr){0};
	ray->p_pos_ori = (t_vctr){0};
	ray->p_dir_ori = (t_vctr){0};
	ray->p_pos.x = parse->p_x;
	ray->p_pos.y = parse->p_y;
	get_dir_vector(parse->facing, ray);
	ray->plane.x = -ray->p_dir.y * 0.66;
	ray->plane.y = ray->p_dir.x * 0.66;
	ray->p_pos_ori.x = parse->p_x;
	ray->p_pos_ori.y = parse->p_y;
	ray->p_dir_ori.x = ray->p_dir.x;
	ray->p_dir_ori.y = ray->p_dir.y;
	ray->plane_ori.x = ray->plane.x;
	ray->plane_ori.y = ray->plane.y;
	ray->move_speed = MOV_SPEED;
	ray->fps = 0;
	return (true);
}

bool	init_mlx_data(t_data *data)
{
	data->xwin = mlx_new_window(data->xdis, W_W, W_H, "cub3D");
	if (!data->xwin)
		return (ft_printf_fd(2, ERR_WIN), false);
	data->ximg = malloc(1 * sizeof(t_oimg));
	if (!data->ximg)
		return (ft_printf_fd(2, E_ALLOC), false);
	data->ximg->ptr = mlx_new_image(data->xdis, W_W, W_H);
	if (!data->ximg->ptr)
		return (ft_printf_fd(2, ERR_IMG), false);
	data->ximg->addr = mlx_get_data_addr(data->ximg->ptr,
			&data->ximg->bpp, &data->ximg->l_l, &data->ximg->endian);
	data->ximg->height = W_H;
	data->ximg->width = W_W;
	return (true);
}
