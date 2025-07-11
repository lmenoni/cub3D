
#include "cub3D.h"

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
	printf("| PX is: %.2f | PY is: %.2f | Facing: %c |\n", data->ray->p_pos->x, data->ray->p_pos->y, parse->facing);
	ft_printf("-----------------------------\n");
	ft_printf("| Map H is: %d | Map W is: %d |\n", data->map_h, data->map_w);
	ft_printf("-----------------------------\n");
	printf("| Dir x: %.2f | Dir y: %.2f |\n", data->ray->p_dir->x, data->ray->p_dir->y);
	ft_printf("-----------------------------\n");
	printf("| Plane x: %.2f | Plane y: %.2f |\n", data->ray->plane->x, data->ray->plane->y);
	ft_printf("-----------------------------\n");
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

void	free_data(t_data *data)
{
	if (data->ray->p_pos)
		free(data->ray->p_pos);
	if (data->ray->p_dir)
		free(data->ray->p_dir);
	if (data->ray->plane)
		free(data->ray->plane);
	if (data->file)
		ft_freemat((void **)data->file, ft_matlen(data->file));
	if (data->map)
		ft_freemat((void **)data->map, ft_matlen(data->map));
	if (data->xwin)
		mlx_destroy_window(data->xdis, data->xwin);
	if (data->ximg)
		mlx_destroy_image(data->xdis, data->ximg);
	if (data->txtr->n_img)
		mlx_destroy_image(data->xdis, data->txtr->n_img);
	if (data->txtr->s_img)
		mlx_destroy_image(data->xdis, data->txtr->s_img);
	if (data->txtr->e_img)
		mlx_destroy_image(data->xdis, data->txtr->e_img);
	if (data->txtr->w_img)
		mlx_destroy_image(data->xdis, data->txtr->w_img);
	mlx_destroy_display(data->xdis);
	free(data->xdis);
}

void	move_forward(t_data *data)
{
	data->ray->p_pos->x += data->ray->p_dir->x * data->ray->move_speed;
	data->ray->p_pos->y += data->ray->p_dir->y * data->ray->move_speed;
}

void	move_backward(t_data *data)
{
	data->ray->p_pos->x -= data->ray->p_dir->x * data->ray->move_speed;
	data->ray->p_pos->y -= data->ray->p_dir->y * data->ray->move_speed;
}

void	move_left(t_data *data)
{
	data->ray->p_pos->x -= data->ray->plane->x * data->ray->move_speed;
	data->ray->p_pos->y -= data->ray->plane->y * data->ray->move_speed;
}

void	move_right(t_data *data)
{
	data->ray->p_pos->x += data->ray->plane->x * data->ray->move_speed;
	data->ray->p_pos->y += data->ray->plane->y * data->ray->move_speed;
}

int	handle_keys(int keycode, t_data *data)
{
	double rotSpeed = 0.05;
	if (keycode == 65307)
		exit(0);
	if (keycode == 119)
		move_forward(data);
	if (keycode == 115)
		move_backward(data);
	if (keycode == 97)
		move_left(data);
	if (keycode == 100)
		move_right(data);
	if (keycode == 61)
		data->ray->move_speed += 0.05;
	if (keycode == 45 && data->ray->move_speed > 0.05)
		data->ray->move_speed -= 0.05;
	if (keycode == 114)
	{
		data->ray->p_pos->x = data->ray->p_pos_ori->x;
		data->ray->p_pos->y = data->ray->p_pos_ori->y;
		data->ray->p_dir->x = data->ray->p_dir_ori->x;
		data->ray->p_dir->y = data->ray->p_dir_ori->y;
	}
	if (keycode == 65361)
	{
		double old_dir_x = data->ray->p_dir->x;
		data->ray->p_dir->x = data->ray->p_dir->x * cos(-rotSpeed) - data->ray->p_dir->y * sin(-rotSpeed);
		data->ray->p_dir->y = old_dir_x * sin(-rotSpeed) + data->ray->p_dir->y * cos(-rotSpeed);

		double old_plane_x = data->ray->plane->x;
		data->ray->plane->x = data->ray->plane->x * cos(-rotSpeed) - data->ray->plane->y * sin(-rotSpeed);
		data->ray->plane->y = old_plane_x * sin(-rotSpeed) + data->ray->plane->y * cos(-rotSpeed);
	}

	// Rotazione a sinistra (←)
	if (keycode == 65363)
	{
		double old_dir_x = data->ray->p_dir->x;
		data->ray->p_dir->x = data->ray->p_dir->x * cos(rotSpeed) - data->ray->p_dir->y * sin(rotSpeed);
		data->ray->p_dir->y = old_dir_x * sin(rotSpeed) + data->ray->p_dir->y * cos(rotSpeed);

		double old_plane_x = data->ray->plane->x;
		data->ray->plane->x = data->ray->plane->x * cos(rotSpeed) - data->ray->plane->y * sin(rotSpeed);
		data->ray->plane->y = old_plane_x * sin(rotSpeed) + data->ray->plane->y * cos(rotSpeed);
	}
	return (0);
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
    if (!parsing(&data, ac, av))
		return (free_data(&data), 1);
	mlx_hook(data.xwin, 2, 1L<<0, handle_keys, &data);
	// mlx_key_hook(data.xwin, handle_keys, &data);
	mlx_loop_hook(data.xdis, engine_render, &data);
	mlx_loop(data.xdis);
	// free_data(&data);
	return (0);
}
