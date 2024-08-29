
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


#define FOV M_PI / 4 
#define RAY_STEP M_PI / 1000
#define PLAYER_SPEED 6
#define ROTATION_SPEED 0.1
#define TRUE 1
#define FALSE 0
#define PI 3.14159265
#define TWO_PI 2 * PI
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
    float rayAngle;
    float wallHitX;
    float wallHitY;
    float distance;
    int wasHitVertical;
    int isRayFacingUp;
    int isRayFacingDown;
    int isRayFacingLeft;
    int isRayFacingRight;
    int wallHitContent;
} t_ray;
typedef struct s_palyer
{
	int			x;
	int			y;
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
	int 		size;
	int			key;
	t_player	player;
	t_ray		ray;
	int dist;
}		t_config;
void	draw_player(t_config **data, int x, int y, int color);
void	draw(t_config **data);
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
void	draw_all_rays(t_config **data);
int		rgb_to_int(int red, int green, int blue);
void castAllRays(t_config *data);
void	draw_line(t_config *data, double x0, double y0, double x1, double y1,
		int color);
		void	draw_player_rays(t_config **data);
void	draw_player_rays(t_config **data);
void	cast_rays(t_config *data);
double chek_vertical(t_config *data, double rayAngle);
double chek_orizental(t_config *data, double rayAngle);
int mapHasWallAt(t_config *data, float x, float y);
double normalizeAngle(double angle);
double distanceBetweenPoints(double x1, double y1, double x2, double y2);
#endif
