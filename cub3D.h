#ifndef CUB3D_H
#define CUB3D_H

# include <X11/keysym.h>
#include "my_libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

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

/*
typedef struct s_vector
{
    double  x; // Coordinata X
    double  y; // Coordinata Y
}           t_vector;

typedef struct  s_player
{
    t_vector pos; // Posizione attuale del giocatore sulla mappa
    t_vector dir; // Direzione in cui il giocatore sta guardando
    t_vector plane; // Piano per il campo visivo (FOV)
    double  move_speed; // Velocità di movimento
    double  rot_speed; // Velocità di rotazione (← →)
}           t_player;

typedef struct  s_map
{
    int     width; // Larghezza della mappa
    int     height; // Altezza della mappa
    char    **grid; // Mappa 2D letta dal file
    int     floor_color; // Colore del pavimento RGB
    int     ceiling_color; // Colore del soffitto RGB
    char    *texture_no; // Path texture Nord
    char    *texture_so; // Path texture Sud
    char    *texture_ea; // Path texture Est
    char    *texture_we; // Path texture Ovest
}           t_map;

typedef struct  s_ray
{
    t_vector ray_dir; // Direzione del raggio
    int     map_x; // Posizione X colpita nella mappa
    int     map_y; // Posizione Y colpita nella mappa
    t_vector delta_dist; // Distanza da percorrere per passare da una griglia all'altra
    t_vector side_dist; //Distanza iniziale da percorrere per il primo impatto con un lato
    int     step_x; // Direzione (+1 o -1) per l'avanzamento su X
    int     step_y; // Direzione (+1 o -1) per l'avanzamento su Y
    int     side; // Indica se il raggio ha colpito un muro verticale
    double  perp_dist; // Distanza corretta tra player e muro
}         t_ray;

typedef struct  s_img
{
    void    *img_ptr; // Puntatore all'immagine
    char    *addr; // Indirizzo dell'immagine
    int     width; // Larghezza dell'immagine
    int     height; // Altezza dell'immagine
    int     bpp; // Bits per pixel
    int     line_length; // Lunghezza della riga in byte
    int     endian; // Endianess dell'immagine
}           t_img;
*/

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

// typedef struct  s_ray
// {
//     double  p_x;
//     double  p_y;
//     double  dir_x;
//     double  dir_y;
//     double  dir_len;
//     double  cam_x;
//     double  cam_y;
//     double  cam_len;
// }           t_ray;

typedef struct  s_txtr
{
    void    *n_img;
    void    *s_img;
    void    *e_img;
    void    *w_img;
    int     f_clr;
    int     c_clr;
}           t_txtr;

typedef struct  s_data
{
    t_txtr  *txtr;
    // ptr ray
    void    *xdis;
    // ptr window
    // ptr w_img
    char    **file;
    char    **map;
    int     map_w;
    int     map_h;
    //in struct ray
    char    facing;//
    int     p_x;//
    int     p_y;//
}           t_data;

void	print_data(t_data *data);

// handle_file.c
char    **read_file(char *path);
char    **add_line(char *line, char **mat);
bool    safe_open(char *path, int *fd);
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
void	clean_up(t_data *data);

#endif