/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:28:40 by igilani           #+#    #+#             */
/*   Updated: 2025/07/22 18:39:32 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	open_door(t_ray *ray, char **map)
{
	int	x;
	int	y;

	x = (int)floor(ray->p_pos.x + ray->p_dir.x);
	y = (int)floor(ray->p_pos.y + ray->p_dir.y);
	if (map[y][x] == 'D')
		map[y][x] = 'd';
	else if (map[y][x] == 'd')
		map[y][x] = 'D';
}