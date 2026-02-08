/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:32:39 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 17:33:16 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	singular_char(char *line, t_parse *parse, int nc)
{
	if (nc == 1 && line[0] == 'E' && !parse->empty_img)
	{
		parse->empty_img = line;
		return (true);
	}
	else if (nc == 1 && line[0] == 'P' && !parse->pause_img)
	{
		parse->pause_img = line;
		return (true);
	}
	else if (nc == 1 && line[0] == 'F' && !parse->f_clr)
	{
		parse->f_clr = line;
		return (true);
	}
	else if (nc == 1 && line[0] == 'C' && !parse->c_clr)
	{
		parse->c_clr = line;
		return (true);
	}
	return (false);
}

bool	map_elements(char *temp, char *line, t_parse *parse, int nc)
{
	if (nc == 2 && ft_strcmp(temp, "PN") == 0 && !parse->pimg_n)
	{
		parse->pimg_n = line;
		return (true);
	}
	else if (nc == 2 && ft_strcmp(temp, "PS") == 0 && !parse->pimg_s)
	{
		parse->pimg_s = line;
		return (true);
	}
	else if (nc == 2 && ft_strcmp(temp, "PE") == 0 && !parse->pimg_e)
	{
		parse->pimg_e = line;
		return (true);
	}
	else if (nc == 2 && ft_strcmp(temp, "PW") == 0 && !parse->pimg_w)
	{
		parse->pimg_w = line;
		return (true);
	}
	return (false);
}

bool	get_element(char *line, t_parse *parse, int nc)
{
	char	*temp;

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
	else if (!singular_char(line, parse, nc)
		&& !map_elements(temp, line, parse, nc))
		return (free(temp), false);
	parse->e_set++;
	free(temp);
	return (true);
}
