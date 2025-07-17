/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:19:15 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/17 18:24:01 by igilani          ###   ########.fr       */
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

bool	get_isma_animation(t_txtr *tx, t_oimg *isma_arr, void *xdis)
{
	int		temp_fd;
	char	*temp_path;
	int		frame;
	char	*temp_n;

	temp_fd = 0;
	frame = 0;
	temp_path = NULL;
	temp_n = NULL;
	isma_arr = malloc(48 * sizeof(t_oimg));
	if (!isma_arr)
		return (ft_printf_fd(2, E_ALLOC), false);
	while (frame < 48)
	{
		temp_path = "texture/animation/frame_";
		temp_n = ft_itoa(frame);
		temp_path = ft_strjoin(temp_path, temp_n);
		free(temp_n);
		temp_path = ft_buffjoin(temp_path, ".xpm");
		temp_fd = open(temp_path, O_RDONLY);
		if (temp_fd == -1)
			return (free(temp_path), perror(FILE_OPEN), free(tx->isma_arr), false);
		close(temp_fd);
		isma_arr[frame].ptr = mlx_xpm_file_to_image(xdis, temp_path, &isma_arr[frame].width, &isma_arr[frame].height);
		isma_arr[frame].addr = mlx_get_data_addr(isma_arr[frame].ptr, &isma_arr[frame].bpp, &isma_arr[frame].l_l, &isma_arr[frame].endian);
		free(temp_path);
		frame++;
	}
	tx->n_isma = 48;
	tx->isma_arr = isma_arr;
	return (true);
}

bool	parse_textures(t_txtr *tx, t_parse *parse, void *xdis)
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
	tx->n_img = get_img_ptr(parse->n_path, xdis);
	tx->s_img = get_img_ptr(parse->s_path, xdis);
	tx->e_img = get_img_ptr(parse->e_path, xdis);
	tx->w_img = get_img_ptr(parse->w_path, xdis);
	tx->player_n = get_img_ptr(parse->pimg_n, xdis);
	tx->player_s = get_img_ptr(parse->pimg_s, xdis);
	tx->player_e = get_img_ptr(parse->pimg_e, xdis);
	tx->player_w = get_img_ptr(parse->pimg_w, xdis);
	tx->empty = get_img_ptr(parse->empty_img, xdis);
	if (!get_isma_animation(tx, tx->isma_arr, xdis))
		return (false);
	if (!tx->n_img || !tx->s_img
		|| !tx->e_img || !tx->w_img
		|| !tx->player_n || !tx->player_s
		|| !tx->player_e || !tx->player_w
		|| !tx->empty)
		return (false);
	return (true);
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
	ray->move_speed = 0.03;
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
