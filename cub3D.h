#ifndef CUB3D_H
#define CUB3D_H

# include <X11/keysym.h>
# include <math.h>
# include "my_libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

# define W_W 1280
# define W_H 768
# define ROT_SPEED 0.09

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

/*

typedef struct  s_player
{
	t_vector 	p_pos; // Posizione attuale del giocatore sulla mappa
	t_vector 	p_dir; // Direzione in cui il giocatore sta guardando
	t_vector 	plane; // Piano per il campo visivo (FOV)
	double  	move_speed; // Velocità di movimento
	double  	rot_speed; // Velocità di rotazione (← →)
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
	t_vector 	ray_dir; // Direzione del raggio
	int     	map_x; // Posizione X colpita nella mappa
	int     	map_y; // Posizione Y colpita nella mappa
	t_vector	delta_dist; // Distanza da percorrere per passare da una griglia all'altra
	t_vector	side_dist; //Distanza iniziale da percorrere per il primo impatto con un lato
	int     	step_x; // Direzione (+1 o -1) per l'avanzamento su X
	int     	step_y; // Direzione (+1 o -1) per l'avanzamento su Y
	int     	side; // Indica se il raggio ha colpito un muro verticale
	double  	perp_dist; // Distanza corretta tra player e muro
}         t_ray;

typedef struct  s_keys
{
	int	 w; // Tasto W premuto
	int	 a; // Tasto A premuto
	int	 s; // Tasto S premuto
	int	 d; // Tasto D premuto
	int	 left; // Tasto freccia sinistra premuto
	int	 right; // Tasto freccia destra premuto
}			   t_keys;

typedef struct	s_game
{
	void		*mlx_ptr; // Puntatore alla libreria grafica
	void		*win_ptr; // Puntatore alla finestra
	int			screen_w; // Larghezza della finestra
	int			screen_h; // Altezza della finestra
	t_player	player; // Stato del giocatore
	t_map		map; // Mappa e dati di configurazione
	t_img		img; // Immagine per il rendering
	t_img		textures[4]; // Array di texture (NO, SO, WE, EA)
	t_keys		keys; // Stato dei tasti premuti
}
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
	char    facing;
	double  p_x;
	double  p_y;
}           t_parse;

typedef struct s_vctr
{
	double  x;
	double  y;
}           t_vctr;

typedef struct  s_ray
{
    t_vctr      p_pos_ori; // Posizione iniziale del player
    t_vctr		p_dir_ori; // Direzione iniziale del player
	t_vctr		p_pos; // Posizione attuale del giocatore sulla mappa
	t_vctr		p_dir; // Direzione in cui il giocatore sta guardando
	t_vctr		plane; // Piano per il campo visivo (FOV)
	t_vctr		ray_dir; // Direzione del raggio
	t_vctr		delta_dist; // Distanza da percorrere per passare da una griglia all'altra
	t_vctr		side_dist; //Distanza iniziale da percorrere per il primo impatto con un lato
	double  	cam_len; // Lunghezza della camera per il calcolo del raggio
	double  	move_speed; // Velocità di movimento
	double  	perp_dist; // Distanza corretta tra player e muro
	int     	map_x; // Posizione X colpita nella mappa
	int     	map_y; // Posizione Y colpita nella mappa
	int     	step_x; // Direzione (+1 o -1) per l'avanzamento su X
	int     	step_y; // Direzione (+1 o -1) per l'avanzamento su Y
	int     	side; // Indica se il raggio ha colpito un muro verticale
	int	 		draw_start; // Inizio della linea da disegnare
	int	 		draw_end; // Fine della linea da disegnare
	int			draw_len;
}         t_ray;

typedef struct  s_oimg
{
	void    *ptr; // Puntatore all'immagine
	char    *addr; // Indirizzo dell'immagine
	int     width; // Larghezza dell'immagine
	int     height; // Altezza dell'immagine
	int     bpp; // Bits per pixel
	int     l_l; // Lunghezza della riga in byte
	int     endian; // Endianess dell'immagine
}           t_oimg;

typedef struct  s_txtr
{
	t_oimg   *n_img;
	t_oimg   *s_img;
	t_oimg   *e_img;
	t_oimg   *w_img;
	int     f_clr;
	int     c_clr;
}           t_txtr;

typedef struct  s_data
{
	t_txtr  *txtr;
	t_ray   *ray;
	t_oimg   *ximg;
	void    *xdis;
	void    *xwin;
	char    **file;
	char    **map;
	int     map_w;
	int     map_h;
}           t_data;

void	print_data(t_data *data, t_parse *parse);
void	free_data(t_data *data);
int		close_window(t_data *data);

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

// engine.c
int		engine_render(t_data *data);
void	set_background(t_data *data);

// dda.c
void	perform_dda(t_data *data, t_ray *ray);
bool	render_outside(t_data *data, t_ray *ray, int *rendered);
void	take_step(t_ray *ray);
void	prepare_ray(t_ray *ray, int x);
void	prepare_steps(t_ray *ray);

// handle_keys.c
int		handle_keys(int keycode, t_data *data);
void	reset(t_ray *ray);
void	key_rotate(t_ray *ray, double rot);
void	move(t_ray *ray, int keycode);

#endif