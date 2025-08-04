/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:56:28 by igilani           #+#    #+#             */
/*   Updated: 2025/07/25 17:56:28 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_remaining_background(t_data *data, int x)
{
	int	y;
	int	offset;

	if (data->ray->draw_start < 0 || data->ray->draw_start > data->ximg->height)
		return ;
	if (data->ray->draw_end < 0 || data->ray->draw_end > data->ximg->height)
		return ;
	y = 0;
	while (y < data->ray->draw_start)
	{
		offset = (y * data->ximg->l_l) + (x * (data->ximg->bpp / 8));
		*((unsigned int *)(data->ximg->addr + offset)) = data->txtr->c_clr;
		y++;
	}
	y = data->ray->draw_end;
	while (y < data->ximg->height)
	{
		offset = (y * data->ximg->l_l) + (x * (data->ximg->bpp / 8));
		*((unsigned int *)(data->ximg->addr + offset)) = data->txtr->f_clr;
		y++;
	}
}

int	engine(t_data *data)
{
	int	x;

	x = 0;
	check_for_movement(data);
	while (x < W_W)
	{
		prepare_ray(data->ray, x);
		perform_dda(data, data->ray);
		compute_projection(data);
		draw_remaining_background(data, x);
		draw_wall_column(data, x);
		x++;
	}
	mlx_put_image_to_window(data->xdis, data->xwin, data->ximg->ptr, 0, 0);
	return (0);
}

bool	parsing(t_data *data, int ac, char **av)
{
	t_parse	parse;

	parse = (t_parse){0};
	if (ac != 2)
		return (ft_printf_fd(2, E_ARG), false);
	data->file = read_file(av[1]);
	if (!data->file)
		return (false);
	if (!get_data(data->file, data, &parse))
		return (false);
	if (!parse_textures(data->txtr, &parse, data->xdis))
	{
		data->map = NULL;
		return (false);
	}
	if (!parse_map(data->map, data, &parse))
		return (false);
	if (!get_vector(&parse, data->ray))
		return (false);
	if (!init_mlx_data(data))
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_txtr	txtr;
	t_ray	ray;

	data = (t_data){0};
	txtr = (t_txtr){0};
	ray = (t_ray){0};
	data.txtr = &txtr;
	data.ray = &ray;
	data.xdis = mlx_init();
	if (!parsing(&data, ac, av))
		return (free_data(&data), 1);
	mlx_hook(data.xwin, 2, 1L << 0, handle_key_press, &data);
	mlx_hook(data.xwin, 3, 1L << 1, handle_key_release, &data);
	mlx_hook(data.xwin, 17, 1L << 2, close_window, &data);
	mlx_loop_hook(data.xdis, engine, &data);
	mlx_loop(data.xdis);
	return (0);
}
