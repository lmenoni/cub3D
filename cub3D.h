#ifndef CUB3D_H
#define CUB3D_H

#include "my_libft/libft.h"

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
    
}           t_data;

// handle_file.c
char    **read_file(char *path);
char    **add_line(char *line, char **mat);
bool    safe_open(char *path, int *fd);
bool	check_file_type(char *path);

#endif