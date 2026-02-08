/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:29:50 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:29:53 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	prepare_steps(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (ray->p_pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - ray->p_pos.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (ray->p_pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - ray->p_pos.y)
			* ray->delta_dist.y;
	}
}

void	prepare_ray(t_ray *ray, int x)
{
	ray->cam_len = 2.0 * x / W_W - 1.0;
	ray->ray_dir.x = ray->p_dir.x + ray->plane.x * ray->cam_len;
	ray->ray_dir.y = ray->p_dir.y + ray->plane.y * ray->cam_len;
	ray->map_x = (int)ray->p_pos.x;
	ray->map_y = (int)ray->p_pos.y;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	prepare_steps(ray);
}

void	take_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

bool	render_outside(t_data *data, t_ray *ray, int *rendered)
{
	if (ray->map_x < 0 || ray->map_x >= data->map_w
		|| ray->map_y < 0 || ray->map_y >= data->map_h)
	{
		(*rendered)++;
		if (*rendered > 30)
		{
			ray->side = -1;
			ray->side_door = -1;
		}
		return (true);
	}
	return (false);
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	ray->side_door = -1;
	while (hit == 0)
	{
		take_step(ray);
		if (data->map[ray->map_y][ray->map_x] == '1'
			|| data->map[ray->map_y][ray->map_x] == 'D')
			hit = 1;
		else if (data->map[ray->map_y][ray->map_x] == 'd' && ISMA == 1)
			hit = 1;
	}
	if (ray->side == -1)
		ray->perp_dist = 0;
	else if (ray->side == 0)
		ray->perp_dist = (ray->map_x - ray->p_pos.x
				+ ((1 - ray->step_x) / 2)) / ray->ray_dir.x;
	else
		ray->perp_dist = (ray->map_y - ray->p_pos.y
				+ ((1 - ray->step_y) / 2)) / ray->ray_dir.y;
}
