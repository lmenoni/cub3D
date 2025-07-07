
#include "cub3D.h"

bool	get_element(char *line, t_parse *parse, int nc)
{
	char *temp;

	temp = ft_strdup(line);
	if (!temp)
		return (ft_printf_fd(2, E_ALLOC), false);
	temp[nc] = '\0';
	if (nc == 2 && ft_strcmp(temp, "NO") == 0 && !parse->n_path)
		parse->n_path = line;
	else if (nc == 2 && ft_strcmp(temp, "SO") == 0 && !parse->s_path)
		parse->s_path = line;
	else if (nc == 2 && ft_strcmp(temp, "EA") == 0 && !parse->e_path)
		parse->e_path = line;
	else if (nc == 2 && ft_strcmp(temp, "WE") == 0 && !parse->w_path)
		parse->w_path = line;
	else if (nc == 1 && line[0] == 'F' && !parse->f_clr)
		parse->f_clr = line;
	else if (nc == 1 && line[0] == 'C' && !parse->c_clr)
		parse->c_clr = line;
	else
		return (free(temp), false);
	parse->e_set++;
	free(temp);
	return (true);
}

bool	parse_line(char *line, t_parse *parse, int line_n)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	skip_spaces(line, &i);
	if (line[i] == '\0')
		return (false);
	while (line[i + j] != '\0' && !is_space(line[i + j]))
		j++;
	if (j > 2 || !get_element(&line[i], parse, j))
		return (ft_printf_fd(2, ELE_INV, (line_n + 1)), false);
	return (true);
}

bool	extract_paths(t_parse *parse, t_data *data)
{
	data->n_path = clean_value(&parse->n_path[2]);
	if (!data->n_path)
		return (false);
	data->s_path = clean_value(&parse->s_path[2]);
	if (!data->s_path)
		return (false);
	data->e_path = clean_value(&parse->e_path[2]);
	if (!data->e_path)
		return (false);
	data->w_path = clean_value(&parse->w_path[2]);
	if (!data->w_path)
		return (false);
	return (true);
}

bool	extract_data(t_parse *parse, t_data *data)
{
	if (!all_set(parse))
		return (false);
	if (!extract_paths(parse, data))
		return (false);
	if (!extract_colors(parse, data))
		return (false);
	return (true);
}

bool	get_data(char **file, t_data *data)
{
	t_parse	parse;
	int		i;

	parse = (t_parse){0};
	i = 0;
	while (file[i])
	{
		if (!is_empty(file[i]))
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
	if (!extract_data(&parse, data))
		return (false);
	return (true);
}
