/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 19:16:06 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/25 19:16:07 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

bool	check_door_sides(char **map, int j, int i)
{
	bool	vertical;
	bool	horizontal;

	vertical = map[j + 1][i] == '1' && map[j - 1][i] == '1'
		&& map[j][i + 1] != '1' && map[j][i - 1] != '1';
	horizontal = map[j][i + 1] == '1' && map[j][i - 1] == '1'
		&& map[j + 1][i] != '1' && map[j - 1][i] != '1';
	if (!(vertical ^ horizontal))
		return (ft_printf_fd(2, "ERROR\nInvalid door positioning.\n"), false);
	return (true);
}

bool	check_invalid_door(char **map)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'D')
			{
				if (!check_door_sides(map, j, i))
					return (false);
			}
			i++;
		}
		j++;
	}
	return (true);
}
