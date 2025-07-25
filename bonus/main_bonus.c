/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 18:38:42 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 18:38:44 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	ray_cast(t_data *data, char *p_addr, int x)
{
	prepare_ray(data->ray, x);
	perform_dda(data, data->ray);
	compute_projection(data, data->ray->perp_dist);
	draw_remaining_background(data, p_addr);
	draw_wall_column(data, p_addr, false);
}

int	engine(t_data *data)
{
	int		x;
	char	*p_addr;

	x = 0;
	if (!data->pause)
	{
		check_for_movement(data);
		while (x < W_W)
		{
			p_addr = data->ximg->addr + (x * (data->ximg->bpp >> 3));
			ray_cast(data, p_addr, x);
			x++;
		}
		hand_open_door(data, data->txtr);
		map_rendering(data, data->txtr);
		mlx_put_image_to_window(data->xdis, data->xwin, data->ximg->ptr, 0, 0);
		print_menu(data);
	}
	else
		pause_render(data);
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
	init_data(&data);
	if (!parsing(&data, ac, av))
		return (free_data(&data), 1);
	mlx_mouse_hide(data.xdis, data.xwin);
	mlx_hook(data.xwin, 2, 1L << 0, handle_key_press, &data);
	mlx_hook(data.xwin, 3, 1L << 1, handle_key_release, &data);
	mlx_hook(data.xwin, 6, 1L << 6, mouse_move, &data);
	mlx_hook(data.xwin, 17, 1L << 2, close_window, &data);
	mlx_loop_hook(data.xdis, engine, &data);
	mlx_loop(data.xdis);
	return (0);
}
