/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:32:38 by igilani           #+#    #+#             */
/*   Updated: 2025/07/23 23:52:16 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	get_door_animation(t_txtr *tx, t_oimg *door_arr, void *xdis)
{
	int		temp_fd;
	char	*temp_path;
	int		frame;
	char	*temp_n;

	temp_fd = 0;
	frame = 0;
	temp_path = NULL;
	temp_n = NULL;
	door_arr = malloc(16 * sizeof(t_oimg));
	if (!door_arr)
		return (ft_printf_fd(2, E_ALLOC), false);
	while (frame < 16)
	{
		temp_path = "texture/animation/door/frame_";
		temp_n = ft_itoa(frame);
		temp_path = ft_strjoin(temp_path, temp_n);
		free(temp_n);
		temp_path = ft_buffjoin(temp_path, ".xpm");
		temp_fd = open(temp_path, O_RDONLY);
		if (temp_fd == -1)
			return (free(temp_path), perror(FILE_OPEN), free(tx->door_arr), false);
		close(temp_fd);
		door_arr[frame].ptr = mlx_xpm_file_to_image(xdis, temp_path, &door_arr[frame].width, &door_arr[frame].height);
		door_arr[frame].addr = mlx_get_data_addr(door_arr[frame].ptr, &door_arr[frame].bpp, &door_arr[frame].l_l, &door_arr[frame].endian);
		free(temp_path);
		frame++;
	}
	tx->n_door = 16;
	tx->door_arr = door_arr;
	return (true);
}

t_oimg	*wall_animation(t_txtr *txtr, int n_img, int ipf)
{
	static int i = -1;

	if (n_img <= 0 || !txtr->isma_arr)
		return (NULL);
	i++;
	if (i == (n_img * ipf) - 1)
		i = 0;
	return (&txtr->isma_arr[i / ipf]);
}

t_oimg	*door_animation(t_txtr *txtr, int frame_index)
{
	if (frame_index < 0 || frame_index >= 16 || !txtr->door_arr)
		return (NULL);
	return (&txtr->door_arr[frame_index]);
}

void	hand_animation(t_data *data, t_ray *ray, t_vctr *new_pos)
{
	if (new_pos->x != ray->p_pos.x || new_pos->y != ray->p_pos.y)
	{
		data->walk_animation_time += 0.1f;
		float bob_offset = sin(data->walk_animation_time) * 15.0f;
		data->hand_height = W_H + (int)bob_offset;
		data->hand_width = W_W + (int)(cos(data->walk_animation_time * 0.5f) * 5.0f);
	}
	else
	{
		if (data->hand_height != W_H)
		{
			int diff = W_H - data->hand_height;
			data->hand_height += diff * 0.1f;
		}
		if (data->hand_width != W_W)
		{
			int diff = W_W - data->hand_width;
			data->hand_width += diff * 0.1f;
		}
	}
}
