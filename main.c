
#include "cub3D.h"

void	print_data(t_data *data)
{
	ft_printf("         DATA PARSING\n");
	ft_printf("-----------------------------\n");
	ft_printf("| NORD path is: %s       |\n", data->n_path);
	ft_printf("-----------------------------\n");
	ft_printf("| SOUTH path is: %s      |\n", data->s_path);
	ft_printf("-----------------------------\n");
	ft_printf("| EAST path is: %s        |\n", data->e_path);
	ft_printf("-----------------------------\n");
	ft_printf("| WEST path is: %s        |\n", data->w_path);
	ft_printf("-----------------------------\n");
	ft_printf("| FLOOR color is: %d  |\n", data->f_clr);
	ft_printf("-----------------------------\n");
	ft_printf("| CEALING color is: %d |\n", data->c_clr);
	ft_printf("-----------------------------\n");
	for (int i = 0; i < ft_matlen(data->map); ++i)
		ft_printf("%s", data->map[i]);
	ft_printf("\n-----------------------------\n");
}

bool    parsing(t_data *data, int ac, char **av)
{
    if (ac != 2)
        return (ft_printf_fd(2, E_ARG), false);
    data->file = read_file(av[1]);
    if (!data->file)
		return (false);
    if (!get_data(data->file, data))
	{
		ft_freemat((void **)data->file, ft_matlen(data->file));
		return (false);
	}
    // if (!parse_map(data->map))//parse della mappa
    //     return (false);
	print_data(data);
    return (true);
}

int main(int ac, char **av)
{
    t_data  data;

    data = (t_data){0};
    if (!parsing(&data, ac, av))
		return (1);
	ft_freemat((void **)data.file, ft_matlen(data.file));
	return (0);
}

//parsing validita' mappa
//non settare piu i path a immagini in data ma subito prima del ritorno di get_data() fare la conversione in img_ptr