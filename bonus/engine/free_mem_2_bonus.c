/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 15:47:15 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 15:47:16 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	free_minimap(t_data *data)
{
	if (data->txtr->player_n)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_n->ptr);
		free(data->txtr->player_n);
	}
	if (data->txtr->player_s)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_s->ptr);
		free(data->txtr->player_s);
	}
	if (data->txtr->player_e)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_e->ptr);
		free(data->txtr->player_e);
	}
	if (data->txtr->player_w)
	{
		mlx_destroy_image(data->xdis, data->txtr->player_w->ptr);
		free(data->txtr->player_w);
	}
	if (data->txtr->empty)
	{
		mlx_destroy_image(data->xdis, data->txtr->empty->ptr);
		free(data->txtr->empty);
	}
}

void	free_utils_images(t_txtr *tx, void *xdis)
{
	if (tx->pause)
	{
		mlx_destroy_image(xdis, tx->pause->ptr);
		free(tx->pause);
	}
	if (tx->hand_sword)
	{
		mlx_destroy_image(xdis, tx->hand_sword->ptr);
		free(tx->hand_sword);
	}
	if (tx->left_hand)
	{
		mlx_destroy_image(xdis, tx->left_hand->ptr);
		free(tx->left_hand);
	}
	if (tx->right_hand)
	{
		mlx_destroy_image(xdis, tx->right_hand->ptr);
		free(tx->right_hand);
	}
}

void	free_door_images(t_txtr *tx, void *xdis)
{
	if (tx->n_door)
	{
		mlx_destroy_image(xdis, tx->n_door->ptr);
		free(tx->n_door);
	}
	if (tx->s_door)
	{
		mlx_destroy_image(xdis, tx->s_door->ptr);
		free(tx->s_door);
	}
	if (tx->e_door)
	{
		mlx_destroy_image(xdis, tx->e_door->ptr);
		free(tx->e_door);
	}
	if (tx->w_door)
	{
		mlx_destroy_image(xdis, tx->w_door->ptr);
		free(tx->w_door);
	}
	if (tx->door)
	{
		mlx_destroy_image(xdis, tx->door->ptr);
		free(tx->door);
	}
}
