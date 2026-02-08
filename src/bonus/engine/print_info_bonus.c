/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igilani <igilani@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:38:17 by igilani           #+#    #+#             */
/*   Updated: 2025/07/22 22:00:07 by igilani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	calculate_fps(t_data *data)
{
	static struct timeval	last_time = {0};
	static int				frame_count = 0;
	struct timeval			current_time;
	double					elapsed_time;

	gettimeofday(&current_time, NULL);
	frame_count++;
	if (last_time.tv_sec == 0)
		last_time = current_time;
	elapsed_time = (current_time.tv_sec - last_time.tv_sec)
		+(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	if (elapsed_time >= 1.0)
	{
		data->ray->fps = (int)(frame_count / elapsed_time);
		frame_count = 0;
		last_time = current_time;
	}
}

void	print_fps(t_data *data, int menu_x)
{
	char	*fps_str;
	char	*fps_num;

	fps_num = ft_itoa(data->ray->fps);
	fps_str = ft_strjoin("FPS: ", fps_num);
	if (fps_str && fps_num)
	{
		mlx_string_put(data->xdis, data->xwin, menu_x, 17, GREEN, fps_str);
		free(fps_str);
		free(fps_num);
	}
}

void	print_commands(t_data *data, int menu_x)
{
	char	*str[8];
	int		i;

	if (data->show_menu)
	{
		mlx_string_put(data->xdis, data->xwin, menu_x, 32, GREY, "CONTROLS:");
		str[0] = "ESC: Exit";
		str[1] = "WASD: Move";
		str[2] = "Mouse/Arrows: Look";
		str[3] = "E: Interact";
		str[4] = "+/-: Speed";
		str[5] = "P: Pause";
		str[6] = "R: Reset";
		str[7] = "I: Toggle info";
		i = -1;
		while (++i < 7)
			mlx_string_put(data->xdis, data->xwin, menu_x, (i + 3) * 15,
				WHITE, str[i]);
	}
	else
		mlx_string_put(data->xdis, data->xwin, menu_x + 30, 12,
			WHITE, "Press I for info");
}

void	print_move_speed(t_data *data, int menu_x)
{
	char	*move_str;
	char	*move_num;

	move_num = ft_itoa((int)(data->ray->move_speed * 100));
	move_str = ft_strjoin("SPEED: ", move_num);
	if (move_str && move_num)
	{
		mlx_string_put(data->xdis, data->xwin, menu_x + 80, 17,
			YELLOW, move_str);
		free(move_str);
		free(move_num);
	}
}

void	print_menu(t_data *data)
{
	int	menu_x;

	calculate_fps(data);
	menu_x = W_W - 140;
	print_commands(data, menu_x);
	if (data->show_menu)
	{
		print_fps(data, menu_x);
		print_move_speed(data, menu_x);
	}
}
