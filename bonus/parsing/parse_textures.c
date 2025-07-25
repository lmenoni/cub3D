/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:42:46 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 17:43:38 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_oimg	*get_img_ptr(char *path, void *mlx)
{
	int		t;
	t_oimg	*temp;

	t = 0;
	t = open(path, O_RDONLY);
	temp = NULL;
	if (t < 0)
	{
		ft_printf_fd(2, FILE_OPEN);
		perror(path);
		return (NULL);
	}
	close(t);
	temp = malloc(1 * sizeof(t_oimg));
	if (!temp)
		return (ft_printf_fd(2, E_ALLOC), temp);
	temp->ptr = mlx_xpm_file_to_image(mlx, path, &temp->width, &temp->height);
	if (!temp->ptr)
		return (ft_printf_fd(2, ERR_IMG_CONV), free(temp), NULL);
	temp->addr = mlx_get_data_addr(temp->ptr, &temp->bpp,
			&temp->l_l, &temp->endian);
	return (temp);
}

bool	check_all_file_type(t_parse *parse)
{
	if (!check_file_type(parse->n_path, ".xpm"))
		return (false);
	if (!check_file_type(parse->s_path, ".xpm"))
		return (false);
	if (!check_file_type(parse->e_path, ".xpm"))
		return (false);
	if (!check_file_type(parse->w_path, ".xpm"))
		return (false);
	if (!check_file_type(parse->pimg_n, ".xpm"))
		return (false);
	if (!check_file_type(parse->pimg_s, ".xpm"))
		return (false);
	if (!check_file_type(parse->pimg_e, ".xpm"))
		return (false);
	if (!check_file_type(parse->pimg_w, ".xpm"))
		return (false);
	if (!check_file_type(parse->empty_img, ".xpm"))
		return (false);
	if (!check_file_type(parse->pause_img, ".xpm"))
		return (false);
	return (true);
}

void	get_standard_images(t_txtr *tx, void *xdis)
{
	tx->s_door = get_img_ptr("texture/doors/south_wall_door.xpm", xdis);
	tx->n_door = get_img_ptr("texture/doors/north_wall_door.xpm", xdis);
	tx->e_door = get_img_ptr("texture/doors/east_wall_door.xpm", xdis);
	tx->w_door = get_img_ptr("texture/doors/west_wall_door.xpm", xdis);
	tx->door = get_img_ptr("texture/doors/door.xpm", xdis);
	tx->hand_sword = get_img_ptr("texture/hands/hand_sword.xpm", xdis);
	tx->left_hand = get_img_ptr("texture/hands/left_hand.xpm", xdis);
	tx->right_hand = get_img_ptr("texture/hands/right_hand.xpm", xdis);
}

void	get_modifiable_images(t_txtr *tx, t_parse *parse, void *xdis)
{
	tx->n_img = get_img_ptr(parse->n_path, xdis);
	tx->s_img = get_img_ptr(parse->s_path, xdis);
	tx->e_img = get_img_ptr(parse->e_path, xdis);
	tx->w_img = get_img_ptr(parse->w_path, xdis);
	tx->player_n = get_img_ptr(parse->pimg_n, xdis);
	tx->player_s = get_img_ptr(parse->pimg_s, xdis);
	tx->player_e = get_img_ptr(parse->pimg_e, xdis);
	tx->player_w = get_img_ptr(parse->pimg_w, xdis);
	tx->empty = get_img_ptr(parse->empty_img, xdis);
	tx->pause = get_img_ptr(parse->pause_img, xdis);
}

bool	parse_textures(t_txtr *tx, t_parse *parse, void *xdis)
{
	if (!check_all_file_type(parse))
		return (false);
	get_standard_images(tx, xdis);
	get_modifiable_images(tx, parse, xdis);
	if (!get_isma_animation(tx, tx->isma_arr, xdis))
		return (false);
	if (!get_portal_animation(tx, tx->portal_arr, xdis))
		return (false);
	if (!tx->n_img || !tx->s_img
		|| !tx->e_img || !tx->w_img
		|| !tx->player_n || !tx->player_s
		|| !tx->player_e || !tx->player_w
		|| !tx->n_door || !tx->s_door
		|| !tx->e_door || !tx->w_door
		|| !tx->empty || !tx->door
		|| !tx->pause || !tx->hand_sword
		|| !tx->left_hand || !tx->right_hand)
		return (false);
	return (true);
}
