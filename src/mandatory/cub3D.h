/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmenoni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:10:25 by lmenoni           #+#    #+#             */
/*   Updated: 2025/07/14 17:10:27 by lmenoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/keysym.h>
# include <math.h>
# include "../my_libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define W_W 1280
# define W_H 768
# define ROT_SPEED 0.003
# define MOV_SPEED 0.03

# define E_ARG "ERROR\nInvalid n of arguments.\n"
# define E_ALLOC "ERROR\nMalloc.\n"
# define CLR_SYN "ERROR\nColor syntax error.\n"
# define CLR_VAL "ERROR\nInvalid color value.\n"
# define ELE_EMPTY "ERROR\nOne or more element's value not set.\n"
# define ELE_VAL "ERROR\nInvalid element value.\n"
# define ELE_INV "ERROR\nUnexpected element at line %d.\n"
# define FILE_OPEN "ERROR\nOpen error "
# define FILE_READ "ERROR\nRead error"
# define FILE_EMPTY "ERROR\nEmpty file as argument.\n"
# define FILE_FORM "ERROR\nInvalid file format, expected %s format.\n"
# define MAP_MSTART "ERROR\nMultiple starting positions.\n"
# define MAP_INV "ERROR\nUnknown character in map.\n"
# define MAP_EMPTY "ERROR\nEmpty line in map.\n"
# define MAP_NULL "ERROR\nNo map found.\n"
# define MAP_NSTART "ERROR\nNo starting position was set.\n"
# define MAP_INC "ERROR\nMap is not incased.\n"
# define ERR_WIN "ERROR\nNew window creation failed.\n"
# define ERR_IMG "ERROR\nNew image creation failed.\n"
# define ERR_IMG_CONV "ERROR\nFile to image conversion failed.\n" 

typedef struct s_parse
{
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*f_clr;
	char	*c_clr;
	int		e_set;
	char	facing;
	double	p_x;
	double	p_y;
}			t_parse;

typedef struct s_oimg
{
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		l_l;
	int		endian;
}			t_oimg;

typedef struct s_draw
{
	t_oimg	*texture;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	int		color;
	double	step;
}				t_draw;

typedef struct s_vctr
{
	double	x;
	double	y;
}			t_vctr;

typedef struct s_ray
{
	t_vctr		p_pos_ori;
	t_vctr		p_dir_ori;
	t_vctr		plane_ori;
	t_vctr		p_pos;
	t_vctr		p_dir;
	t_vctr		plane;
	t_vctr		ray_dir;
	t_vctr		delta_dist;
	t_vctr		side_dist;
	double		cam_len;
	double		move_speed;
	double		perp_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
	int			draw_start;
	int			draw_end;
	int			draw_len;
}				t_ray;

typedef struct s_txtr
{
	t_oimg	*n_img;
	t_oimg	*s_img;
	t_oimg	*e_img;
	t_oimg	*w_img;
	int		f_clr;
	int		c_clr;
}			t_txtr;

typedef struct s_data
{
	t_txtr	*txtr;
	t_ray	*ray;
	t_oimg	*ximg;
	void	*xdis;
	void	*xwin;
	char	**file;
	char	**map;
	int		map_w;
	int		map_h;
	int		moving;
	int		rotating;
}			t_data;

// handle_file.c
char	**read_file(char *path);
char	**add_line(char *line, char **mat);
bool	safe_open(char *path, int *fd);
bool	check_file_type(char *path, char *format);

// parsing_utils.c
bool	is_int(char *s);
bool	is_empty(char *str);
char	*clean_value(char	*line);
bool	all_set(t_parse *parse);

// extract_elements.c
bool	get_element(char *line, t_parse *parse, int nc);
bool	parse_line(char *line, t_parse *parse, int line_n);
bool	extract_paths(t_parse *parse);
bool	extract_data(t_parse *parse, t_data *data);
bool	get_data(char **file, t_data *data, t_parse *parse);

// extract_colors.c
bool	check_int(char **comp, int *r, int *g, int *b);
bool	check_syntax(char *s);
int		convert_color(char *s);
bool	extract_colors(t_parse *parse, t_data *data);

// parse_map.c
bool	parse_map(char **map, t_data *data, t_parse *parse);
bool	incased(char **map, t_data *data, t_parse *parse);
bool	check_characters(char **map, t_data *data);
char	**normalize_map(char **map, t_data *data, t_parse *parse);

// parse_map_utils.c
bool	bool_fill(char **map, t_data *data, int y, int x);
void	copy_row(char *r, char *s, int y, t_parse *parse);
bool	invalid_char(char *s, t_data *data);
bool	multiple_start(char c);
void	clean_up(t_data *data);

// init_data.c
bool	init_mlx_data(t_data *data);
bool	get_vector(t_parse *parse, t_ray *ray);
void	get_dir_vector(char face, t_ray *ray);
bool	parse_textures(t_txtr *tx, t_parse *parse, void *xdis);
t_oimg	*get_img_ptr(char *path, void *mlx);

// dda.c
void	perform_dda(t_data *data, t_ray *ray);
bool	render_outside(t_data *data, t_ray *ray, int *rendered);
void	take_step(t_ray *ray);
void	prepare_ray(t_ray *ray, int x);
void	prepare_steps(t_ray *ray);

// handle_keys.c
int		handle_key_press(int keycode, t_data *data);
int		handle_key_release(int keycode, t_data *data);
int		close_window(t_data *data);

// draw.c
void	draw_wall_column(t_data *data, int x);
void	drawing_loop(t_draw *temp, t_data *data, int x);
int		get_texture_x_coordinate(t_draw *temp, t_data *data);
t_oimg	*get_texture(t_data *data);

// draw_utils.c
void	set_background(t_data *data);
void	my_pixel_put(int x, int y, t_data *data, int color);
void	compute_projection(t_data *data);

// handle_keys_utils.c
void	check_for_movement(t_data *data);
void	reset(t_ray *ray);
void	key_rotate(t_ray *ray, double rot);
void	move(t_ray *ray, int keycode);

// free_mem.c
void	free_data(t_data *data);
void	free_images(t_data *data);

#endif
