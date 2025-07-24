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

void	put_image_to_image(t_data *data, t_oimg *in, int x, int y)
{
	int				i;
	int				j;
	int	color;
	// char			*dst_addr;

	i = 0;
	j = 0;
	color = 0;
	while (j < in->height)
	{
		i = 0;
		while (i < in->width)
		{
			// color = *(unsigned int *)(in->addr
			// 		+ (j * in->l_l)
			// 		+ (i * (in->bpp >> 3)));
			if ((x + i) >= 0 && (x + i) < data->ximg->width
				&& (y + j) >= 0 && (y + j) < data->ximg->height)
				{
					color = *(unsigned int *)(in->addr
							+ (j * in->l_l)
							+ (i * (in->bpp >> 3)));
					my_pixel_put(x + i, y + j, data, color);
				}
				// {
				// 	color = *(unsigned int *)(in->addr
				// 			+ (j * in->l_l)
				// 			+ (i * (in->bpp >> 3)));
				// 	if (color != 0x75ff75)
				// 	{
				// 		dst_addr = data->ximg->addr + (y + j) * data->ximg->l_l + (x + i) * (data->ximg->bpp >> 3);
				// 		*((unsigned int *)dst_addr) = color;
				// 	}
				// }
			i++;
		}
		j++;
	}
}

void	render_map(t_data *data, t_oimg *player, t_txtr *txtr)
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
		x = MAP_POS;
		while (i < (int)data->ray->p_pos.x + 7)
		{
			if (i < data->map_w && i >= 0 && j < data->map_h && j >= 0 && (data->map[j][i] == '0' || data->map[j][i] == 'd'))
			{
				if (j == (int)data->ray->p_pos.y && i == (int)data->ray->p_pos.x)
					put_image_to_image(data, player, x, y);
				else
					put_image_to_image(data, txtr->empty, x, y);
			}
			i++;
			x += txtr->empty->width;
		}
		j++;
		y += txtr->empty->height;
	}
}

void	map_rendering(t_data *data, t_txtr *txtr)
{
	if (fabs(data->ray->p_dir.x) > fabs(data->ray->p_dir.y))
	{
		if (data->ray->p_dir.x > 0)
			render_map(data, txtr->player_e, txtr);
		else
			render_map(data, txtr->player_w, txtr);
	}
	else
	{
		if (data->ray->p_dir.y > 0)
			render_map(data, txtr->player_s, txtr);
		else
			render_map(data, txtr->player_n, txtr);
	}
}

int	engine(t_data *data)
{
	int	x;
	char *p_addr;

	x = 0;
	if (!data->pause)
	{
		check_for_movement(data);
		update_door_animation(data);
		while (x < W_W)
		{
			p_addr = data->ximg->addr + (x * (data->ximg->bpp >> 3)); 
			prepare_ray(data->ray, x);
			perform_dda(data, data->ray);
			compute_projection(data, data->ray->perp_dist);
			draw_remaining_background(data, p_addr);
			draw_wall_column(data, p_addr, false);
			// if (data->ray->side_door != -1)
			// {
			// 	compute_projection(data, data->ray->perp_dist_door);
			// 	draw_wall_column(data, p_addr, true);
			// }
			x++;
		}
		hand_open_door(data);
		map_rendering(data, data->txtr);
		mlx_put_image_to_window(data->xdis, data->xwin, data->ximg->ptr, 0, 0);
		print_menu(data);
	}
	else
	{
		t_oimg *pause_frame;
		pause_frame = wall_animation(data->txtr, data->txtr->n_isma, 350);
		mlx_put_image_to_window(data->xdis, data->xwin, pause_frame->ptr, ((W_W - pause_frame->width) / 2), ((W_H - pause_frame->height) / 2));
	}
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
	data.hand_status = 0;
	data.hand_timer = 0;
	data.door_animation_state = 0;
	data.door_animation_frame = 0;
	data.door_animation_timer = 0;
	data.door_pos_x = -1;
	data.door_pos_y = -1;
	data.hand_width = W_W;
	data.hand_height = W_H;
	data.walk_animation_time = 0.0f;
	data.xdis = mlx_init();
	
	data.hand_sword = malloc(1 * sizeof(t_oimg));
	*data.hand_sword = (t_oimg){0};
	data.hand_sword->ptr = mlx_xpm_file_to_image(data.xdis, "texture/hand_sword.xpm", &data.hand_sword->width, &data.hand_sword->height);
	data.hand_sword->addr = mlx_get_data_addr(data.hand_sword->ptr, &data.hand_sword->bpp, &data.hand_sword->l_l, &data.hand_sword->endian);

	data.right_hand = malloc(1 * sizeof(t_oimg));
	*data.right_hand = (t_oimg){0};
	data.right_hand->ptr = mlx_xpm_file_to_image(data.xdis, "texture/right_hand.xpm", &data.right_hand->width, &data.right_hand->height);
	data.right_hand->addr = mlx_get_data_addr(data.right_hand->ptr, &data.right_hand->bpp, &data.right_hand->l_l, &data.right_hand->endian);

	data.left_hand = malloc(1 * sizeof(t_oimg));
	*data.left_hand = (t_oimg){0};
	data.left_hand->ptr = mlx_xpm_file_to_image(data.xdis, "texture/left_hand.xpm", &data.left_hand->width, &data.left_hand->height);
	data.left_hand->addr = mlx_get_data_addr(data.left_hand->ptr, &data.left_hand->bpp, &data.left_hand->l_l, &data.left_hand->endian);
	
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
