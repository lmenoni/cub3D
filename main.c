
#include "cub3D.h"

bool	get_element(char *line, t_parse *parse, int nc)
{
	line[nc] = '\0';
	if (nc == 2 && ft_strcmp(line, "NO") == 0 && !parse->n_path)
		parse->n_path = line;
	else if (nc == 2 && ft_strcmp(line, "SO") == 0 && !parse->s_path)
		parse->s_path = line;
	else if (nc == 2 && ft_strcmp(line, "EA") == 0 && !parse->e_path)
		parse->e_path = line;
	else if (nc == 2 && ft_strcmp(line, "WE") == 0 && !parse->w_path)
		parse->w_path = line;
	else if (nc == 1 && line[0] == 'F' && !parse->f_clr)
		parse->f_clr = line;
	else if (nc == 1 && line[0] == 'C' && !parse->c_clr)
		parse->c_clr = line;
	else
		return (false);
	parse->e_set++;
	return (true);
}

bool	is_empty(char *str)
{
	int i;

	i = 0;
	skip_spaces(str, &i);
	if (str[i] == '\0')
		return (true);
	return (false);
}

bool	parse_line(char *line, t_parse *parse, int line_n)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	skip_spaces(line, &i);
	while (!is_space(line[i + j]))
		j++;
	if (j > 2 || !get_element(&line[i], parse, j))
		return (ft_printf_fd(2, "ERROR\nUnexpected element at line %d.\n", line_n), false);
	return (true);
}

bool	extract_data(t_parse *parse, t_data *data)
{

}

bool	get_data(char **file, t_data *data)
{
	t_parse	parse;
	int		i:

	parse = (t_parse){0};
	i = 0;
	while (file[i])
	{
		if (!is_empty(line[i]))
		{
			if (parse.e_set == 6)
			{
				data->map = &file[i];
				break ;
			}
			if (!parse_line(file[i], &parse, i))
				return (false);
		}
		i++;
	}
	if (!extract_data(&parse, data))// effettiva estrazione dati gia parsati e inseriti in data
		return (false);
	return (true);
}

bool    parsing(t_data *data, int ac, char **av)
{
    char    **file;

	(void)data;
    file = NULL;
    if (ac != 2)
        return (ft_printf_fd(2, "ERROR\nInvalid n of arguments.\n"), false);
    file = read_file(av[1]);
    if (!file)
		return (false);
	// for (int i = 0; i < ft_matlen(file); ++i)
	// 	ft_printf("%s", file[i]);
    if (!get_data(file, data))//parsing sui dati nel file, estrazione e salvataggio in data dei dati
        return (false);
    // if (!parse_map(data->map))//parse della mappa
    //     return (false);
    return (true);
}

int main(int ac, char **av)
{
    t_data  data;

    data = (t_data){0};
    if (!parsing(&data, ac, av))
        return (1);
}

//estrazione dati da array file
//parsing validita' mappa