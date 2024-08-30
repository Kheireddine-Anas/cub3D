
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
#define S_W 1500
#define RAY_STEP M_PI / 1800
#define PLAYER_SPEED_MINI_MAP 2.7
#define PLAYER_SPEED   PLAYER_SPEED_MINI_MAP * 4
#define ROTATION_SPEED 0.2
#define TRUE 1
#define FALSE 0
#define size_ 8
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
	int			x_mini;
	int			y_mini;
	double		angle;
	float		fov_rd;
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
	double			move_x;
	double			move_y;
	double			move_x_min;
	double			move_y_min;
	int 		size;
	int			size_mini_map;
	int			key;
	t_player	player;
	t_ray		ray;
	int dist;
}		t_config;
void	draw_player(t_config **data, int x, int y, int color);
void	draw_mini_map(t_config **data);
void	free_doube_eraay(char **str);
void	destroy_data(t_config **data);
void	fontion_mlx_and_draw(t_config **data);
void	map_inistialisation(t_config **data);
void	chek_argument_and_extention(int err, char *map_name);
void	struct_instialisation(t_config **data, char *map_name);
void	get_height_map(t_config **data);
void	free_double_array(char **str);
char	*delet_newlin(char *str);
int		open_map(t_config **data);
void	error_intalis(t_config ** data);
int		close_window(t_config **data);
void	calcul_size(t_config **data);
void	draw_square(t_config **data, int x, int y, int color);
void	castAllRays(t_config **data);
void	draw_line(t_config *data, double x0, double y0, double x1, double y1,
		int color);
double	check_vertical(t_config *data, double rayAngle);
double	check_horizontal(t_config *data, double rayAngle);
double	normalizeAngle(double angle);
double	distanceBetweenPoints(double x1, double y1, double x2, double y2);
void render_wall(t_config *data, int ray, double distance,  double angle);
void    castAllRays_minimap(t_config *data);
double check_horizontal_mini(t_config *data, double rayAngle);
double check_vertical_mini(t_config *data, double rayAngle);
#endif
