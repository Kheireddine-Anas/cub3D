
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdlib.h>
# include <string.h>
# include "getNextLine/get_next_line.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include "fcntl.h"
#include <float.h> 


#define FOV 60
# define S_W 1900
# define S_H 1000
# define TILE_SIZE 10
#define size_ 10
#define RAY_STEP M_PI / 1800
#define PLAYER_SPEED  2
#define PLAYER_SPEED_MINI_MAP PLAYER_SPEED 
#define ROTATION_SPEED 0.1
#define TRUE 1
#define FALSE 0
#define TWO_PI 2 * M_PI
# define BLK 0x000000FF
# define GREY 0x808080
# define BLU 0x87CEEBFF
# define GREN 0x008000FF
# define ORNG 0xFF9300FF
# define RED 0xFF0000FF
# define WHI 0xFFFFF
# define NUM_RAYS 1000

typedef struct s_map
{
	int			fd;
	char		**map_buffer;
	int			map_width;
	int			map_height;
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*floor_color;
	char		*ceiling_color;
}		t_map;
typedef struct s_ray
{
	int		index;
	double	ray_ngl;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	double	distance;
	int		flag;
}	t_ray;
typedef struct s_palyer
{
	int			x;
	int			y;
	double			x_mini;
	double			y_mini;
	double		angle;
	double		fov_rd;
}		t_player;
typedef struct s_config
{
	t_map		*map;
	char		*map_name;
	int			fd_map;
	int			counter;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	int			width_window;
	int			height_window;
	double		mouv_camera_left;
	double				move_x;
	double				move_y;
	mlx_texture_t	*texture_or;
	mlx_texture_t	*texture_ver;
	int 		size;
	int			size_mini_map;
	int			key;
	int dor_x;
	int dor_y;
	t_player	player;
	t_ray		ray;
	int flag;
	int dist;
	int strat_x;
	int strat_y;
	int end_x;
	int end_y;
}		t_config;
void draw_update(t_config **data);
void cherch_pos_dor(t_config **data);
void    castAllRays_minimap(t_config *data);
void open_dor(t_config **data);
void	draw(t_config **data);
void	free_doube_eraay(char **str);
void 	draw_card(t_config *data);
void	destroy_data(t_config **data);
void	fontion_mlx_and_draw(t_config **data);
void	map_inistialisation(t_config **data);
void	chek_argument_and_extention(int err, char *map_name);
void	struct_instialisation(t_config **data, char *map_name);
void draw_img(t_config **data);
void	get_height_map(t_config **data);
void	free_double_array(char **str);
char	*delet_newlin(char *str);
int		open_map(t_config **data);
void	error_intalis(t_config ** data);
int		close_window(t_config **data);
void	calcul_size(t_config **data);
void	draw_square(t_config **data, int x, int y, int color);
void draw_square_player(t_config **data, int x, int y, int color);
void	castAllRays(t_config **data);
void	draw_line(t_config *data, double x0, double y0, double x1, double y1,
		int color);
double	check_vertical(t_config **data, double rayAngle);
double	check_horizontal(t_config **data, double rayAngle);
double	normalizeAngle(double angle);
double	distanceBetweenPoints(double x1, double y1, double x2, double y2);
void render_wall(t_config **data, int ray, double distance,  double angle);
void    castAllRays_minimap(t_config *data);
double check_horizontal_mini(t_config *data, double rayAngle);
double check_vertical_mini(t_config *data, double rayAngle);
void draw_star(t_config *data, int center_x, int center_y, int radius);
#endif
