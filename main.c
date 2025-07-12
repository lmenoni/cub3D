
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
	printf("| PX is: %.2f | PY is: %.2f | Facing: %c |\n", data->ray->p_pos.x, data->ray->p_pos.y, parse->facing);
	ft_printf("-----------------------------\n");
	ft_printf("| Map H is: %d | Map W is: %d |\n", data->map_h, data->map_w);
	ft_printf("-----------------------------\n");
	printf("| Dir x: %.2f | Dir y: %.2f |\n", data->ray->p_dir.x, data->ray->p_dir.y);
	ft_printf("-----------------------------\n");
	printf("| Plane x: %.2f | Plane y: %.2f |\n", data->ray->plane.x, data->ray->plane.y);
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

void	free_images(t_data *data)
{
	if (data->ximg)
	{
		mlx_destroy_image(data->xdis, data->ximg->ptr);
		free(data->ximg);
	}
	if (data->txtr->n_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->n_img->ptr);
		free(data->txtr->n_img);
	}
	if (data->txtr->s_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->s_img->ptr);
		free(data->txtr->s_img);
	}
	if (data->txtr->e_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->e_img->ptr);
		free(data->txtr->e_img);
	}
	if (data->txtr->w_img)
	{
		mlx_destroy_image(data->xdis, data->txtr->w_img->ptr);
		free(data->txtr->w_img);
	}
}

void	free_data(t_data *data)
{
	if (data->file)
		ft_freemat((void **)data->file, ft_matlen(data->file));
	if (data->map)
		ft_freemat((void **)data->map, ft_matlen(data->map));
	if (data->xwin)
		mlx_destroy_window(data->xdis, data->xwin);
	free_images(data);
	mlx_destroy_display(data->xdis);
	free(data->xdis);
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
	mlx_loop_hook(data.xdis, engine_render, &data);
	mlx_loop(data.xdis);
	return (0);
}
