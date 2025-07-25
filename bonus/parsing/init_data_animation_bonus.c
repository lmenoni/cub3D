/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_animation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:18:46 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 17:42:13 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

char	*get_temp_ani_path(char *beginning, int frame)
{
	char	*temp_path;
	char	*temp_n;

	temp_path = NULL;
	temp_n = NULL;
	temp_n = ft_itoa(frame);
	temp_path = ft_strjoin(beginning, temp_n);
	free(temp_n);
	temp_path = ft_buffjoin(temp_path, ".xpm");
	return (temp_path);
}

bool	fill_animation_arr(t_oimg *arr, int size, char *path, void *xdis)
{
	int		frame;
	char	*temp_path;
	t_oimg	*temp_img;

	frame = 0;
	while (frame < size)
	{
		temp_path = get_temp_ani_path(path, frame);
		temp_img = get_img_ptr(temp_path, xdis);
		if (!temp_img)
			return (free(temp_path), free_img_arr(arr, frame, xdis), false);
		arr[frame] = *temp_img;
		free(temp_img);
		free(temp_path);
		frame++;
	}
	return (true);
}

bool	get_portal_animation(t_txtr *tx, t_oimg *portal_arr, void *xdis)
{
	portal_arr = malloc(82 * sizeof(t_oimg));
	if (!portal_arr)
		return (ft_printf_fd(2, E_ALLOC), false);
	if (!fill_animation_arr(portal_arr, 82
			, "texture/animation/portal/frame_", xdis))
		return (false);
	tx->n_portal = 82;
	tx->portal_arr = portal_arr;
	return (true);
}

bool	get_isma_animation(t_txtr *tx, t_oimg *isma_arr, void *xdis)
{
	isma_arr = malloc(48 * sizeof(t_oimg));
	if (!isma_arr)
		return (ft_printf_fd(2, E_ALLOC), false);
	if (!fill_animation_arr(isma_arr, 48
			, "texture/animation/isma/frame_", xdis))
		return (false);
	tx->n_isma = 48;
	tx->isma_arr = isma_arr;
	return (true);
}
