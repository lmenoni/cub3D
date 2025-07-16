
#include "cub3D_bonus.h"

void	print_data(t_data *data, t_parse *parse)
{
	ft_printf("         DATA PARSING\n");
	ft_printf("-----------------------------\n");
	ft_printf("| FLOOR color is: %d  |\n", data->txtr->f_clr);
	ft_printf("-----------------------------\n");
	ft_printf("| CEALING color is: %d |\n", data->txtr->c_clr);
	ft_printf("-----------------------------\n");
	for (int i = 0; i < ft_matlen(data->map); ++i)
		ft_printf("%s\n", data->map[i]);
	ft_printf("-----------------------------\n");
	printf("| PX is: %.2f | PY is: %.2f | Facing: %c |\n", data->ray->p_pos.x, data->ray->p_pos.y, parse->facing);
	ft_printf("-----------------------------\n");
	ft_printf("| Map H is: %d | Map W is: %d |\n", data->map_h, data->map_w);
	ft_printf("-----------------------------\n");
	printf("| Dir x: %.2f | Dir y: %.2f |\n", data->ray->p_dir.x, data->ray->p_dir.y);
	ft_printf("-----------------------------\n");
	printf("| Plane x: %.2f | Plane y: %.2f |\n", data->ray->plane.x, data->ray->plane.y);
	ft_printf("-----------------------------\n");
}

void	draw_remaining_background(t_data *data, int x)
{
	int y;
	int offset;

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

void	render_map(t_data *data, t_oimg *player)
{
	int	x;
	int y;
	int i;
	int j;

	x = MAP_POS;
	y = MAP_POS;
	i = (int)data->ray->p_pos.x - 7;
	j = (int)data->ray->p_pos.y - 7;
	while (j < (int)data->ray->p_pos.y + 7)
	{
		i = (int)data->ray->p_pos.x - 7;
		x = 0;
		while (i < (int)data->ray->p_pos.x + 7)
		{
			if (i < data->map_w && i >= 0 && j < data->map_h && j >= 0 && data->map[j][i] == '0')
			{
				if (j == (int)data->ray->p_pos.y && i == (int)data->ray->p_pos.x)
					mlx_put_image_to_window(data->xdis, data->xwin, player->ptr, x, y);
				else
					mlx_put_image_to_window(data->xdis, data->xwin, data->empty.ptr, x, y);
			}
			i++;
			x += data->empty.width;
		}
		j++;
		y += data->empty.height;
	}
}

void	map_rendering(t_data *data)
{
	if (fabs(data->ray->p_dir.x) > fabs(data->ray->p_dir.y))
	{
		if (data->ray->p_dir.x > 0)
			render_map(data, &data->player_e);
		else
			render_map(data, &data->player_w);
	}
	else
	{
		if (data->ray->p_dir.y > 0)
			render_map(data, &data->player_s);
		else
			render_map(data, &data->player_n);
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
	print_menu(data);
	map_rendering(data);
	return (0);
}

bool    parsing(t_data *data, int ac, char **av)
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
	print_data(data, &parse);
	return (true);
}

int main(int ac, char **av)
{
	t_data  data;
	t_txtr	txtr;
	t_ray	ray;

	data = (t_data){0};
	txtr = (t_txtr){0};
	ray = (t_ray){0};
	data.txtr = &txtr;
	data.ray = &ray;
	data.xdis = mlx_init();
	data.player_n.ptr = mlx_xpm_file_to_image(data.xdis, "texture/player_n.xpm", &data.player_n.width, &data.player_n.height);
	data.player_s.ptr = mlx_xpm_file_to_image(data.xdis, "texture/player_s.xpm", &data.player_s.width, &data.player_s.height);
	data.player_e.ptr = mlx_xpm_file_to_image(data.xdis, "texture/player_e.xpm", &data.player_e.width, &data.player_e.height);
	data.player_w.ptr = mlx_xpm_file_to_image(data.xdis, "texture/player_w.xpm", &data.player_w.width, &data.player_w.height);
	data.empty.ptr = mlx_xpm_file_to_image(data.xdis, "texture/empty.xpm", &data.empty.width, &data.empty.height);
	if (!parsing(&data, ac, av))
		return (free_data(&data), 1);
	mlx_mouse_hide(data.xdis, data.xwin);
	mlx_hook(data.xwin, 2, 1L<<0, handle_key_press, &data);
	mlx_hook(data.xwin, 3, 1L<<1, handle_key_release, &data);
	mlx_hook(data.xwin, 6, 1L << 6, mouse_move, &data);
	mlx_hook(data.xwin, 17, 1L << 2, close_window, &data);
	mlx_loop_hook(data.xdis, engine, &data);
	mlx_loop(data.xdis);
	return (0);
}
