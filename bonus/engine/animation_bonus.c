/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:32:38 by igilani           #+#    #+#             */
/*   Updated: 2025/07/18 14:11:53 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*wall_animation(t_data *data, t_txtr *txtr, int n_img)
{
	static int i = -1;

	(void)data;
	if (n_img <= 0 || !txtr->isma_arr)
		return (NULL);
	i++;
	if (i == (n_img * 20000) - 1)
		i = 0;
	return (&txtr->isma_arr[i / 20000]);
}