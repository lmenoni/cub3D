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
int	convert_color(char *s);
bool	extract_colors(t_parse *parse, t_data *data);

#endif