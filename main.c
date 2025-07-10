
#include "cub3D.h"

void	print_data(t_data *data)
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
	ft_printf("| PX is: %d | PY is: %d | Facing: %c |\n", data->p_x, data->p_y, data->facing);
	ft_printf("-----------------------------\n");
	ft_printf("| Map H is: %d | Map W is: %d |\n", data->map_h, data->map_w);
	ft_printf("-----------------------------\n");
}

void	*get_img_ptr(char *path, void *mlx)
{
	int	t;
	void	*temp;
	int		width;
	int		height;

	t = 0;
	width = 0;
	height = 0;
	t = open(path, O_RDONLY);
	if (t < 0)
	{
		ft_printf_fd(2, FILE_OPEN);
		perror(path);
		return (false);
	}
	close(t);
	temp = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!temp)
		ft_printf_fd(2, "ERROR\nFile to image conversion failed.\n");
	return (temp);
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
	tx->n_img = get_img_ptr(parse->n_path, xdis);
	tx->s_img = get_img_ptr(parse->s_path, xdis);
	tx->n_img = get_img_ptr(parse->e_path, xdis);
	tx->n_img = get_img_ptr(parse->w_path, xdis);
	if (!tx->n_img || !tx->s_img
		|| !tx->e_img || !tx->s_img)
		return (false);
	return (true);
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
	if (!parse_map(data->map, data))
		return (false);
	print_data(data);
    return (true);
}

void	free_data(t_data *data)
 {
	if (data->file)
		ft_freemat((void **)data->file, ft_matlen(data->file));
	if (data->map)
		ft_freemat((void **)data->map, ft_matlen(data->map));
	mlx_destroy_display(data->xdis);
	free(data->xdis);
 }

int main(int ac, char **av)
{
    t_data  data;
	t_txtr	txtr;

    data = (t_data){0};
	txtr = (t_txtr){0};
	data.txtr = &txtr;
	data.xdis = mlx_init();
    if (!parsing(&data, ac, av))
		return (free_data(&data), 1);
	free_data(&data);
	return (0);
}

//non settare piu i path a immagini in data ma subito prima del ritorno di get_data() fare la conversione in img_ptr