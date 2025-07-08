#ifndef CUB3D_H
#define CUB3D_H

#include "my_libft/libft.h"

# define E_ARG "ERROR\nInvalid n of arguments.\n"
# define E_ALLOC "ERROR\nMalloc.\n"
# define CLR_SYN "ERROR\nColor syntax error.\n"
# define CLR_VAL "ERROR\nInvalid color value.\n"
# define ELE_EMPTY "ERROR\nOne or more element's value not set.\n"
# define ELE_VAL "ERROR\nInvalid element value.\n"
# define ELE_INV "ERROR\nUnexpected element at line %d.\n"
# define FILE_OPEN "ERROR\nOpen error"
# define FILE_READ "ERROR\nRead error"
# define FILE_EMPTY "ERROR\nEmpty file as argument.\n"
# define FILE_FORM "ERROR\nInvalid file format, expected .cub format.\n"
# define MAP_MSTART "ERROR\nMultiple starting positions.\n"
# define MAP_INV "ERROR\nUnknown character in map.\n"
# define MAP_EMPTY "ERROR\nEmpty line in map.\n"
# define MAP_NULL "ERROR\nNo map found.\n"
# define MAP_NSTART "ERROR\nNo starting position was set.\n"
# define MAP_INC "ERROR\nMap is not incased.\n"

typedef struct  s_parse
{
    char    *n_path;
    char    *s_path;
    char    *e_path;
    char    *w_path;
    char    *f_clr;
    char    *c_clr;
    int     e_set;
}           t_parse;

typedef struct  s_data
{
    char    **map;
    int     map_w;
    int     map_h;
    char    facing;
    int     p_x;
    int     p_y;
    char    *n_path;
    char    *s_path;
    char    *e_path;
    char    *w_path;
    int     f_clr;
    int     c_clr;
    char    **file;
}           t_data;

// handle_file.c
char    **read_file(char *path);
char    **add_line(char *line, char **mat);
bool    safe_open(char *path, int *fd);
bool	check_file_type(char *path);

// parsing_utils.c
bool	is_int(char *s);
bool	is_empty(char *str);
char	*clean_value(char	*line);
bool	all_set(t_parse *parse);

// extract_elements.c
bool	get_element(char *line, t_parse *parse, int nc);
bool	parse_line(char *line, t_parse *parse, int line_n);
bool	extract_paths(t_parse *parse, t_data *data);
bool	extract_data(t_parse *parse, t_data *data);
bool	get_data(char **file, t_data *data);

// extract_colors.c
bool	check_int(char **comp, int *r, int *g, int *b);
bool	check_syntax(char *s);
int     convert_color(char *s);
bool	extract_colors(t_parse *parse, t_data *data);

// parse_map.c
bool	parse_map(char **map, t_data *data);
bool	incased(char **map, t_data *data);
bool	check_characters(char **map, t_data *data);
char	**normalize_map(char **map, t_data *data);

// parse_map_utils.c
bool	bool_fill(char **map, t_data *data, int y, int x);
void	copy_row(char *r, char *s, int y, t_data *data);
bool	invalid_char(char *s, t_data *data);
bool	multiple_start(char c);

#endif