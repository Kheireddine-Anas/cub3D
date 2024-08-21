
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

#define FOV M_PI / 2 
#define RAY_STEP M_PI / 1000
#define MOVE_STEP 6
#define ROTATION_ANGLE 0.1
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

typedef struct s_palyer
{
	int			x;
	int			y;
	double		angle;

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
	int			mouv_left;
	int			mouv_rigt;
	int			mouv_up;
	int			mouv_down;
	int			width;
	int			height;
	int			width_window;
	int			height_window;
	double		mouv_camera_left;
	int			mouve_palyer_left;
	int			mouve_palyer_haut;
	int 		size;
	int			key;
	t_player	player;
}		t_config;

void	my_mlx_pixel_put(t_config **data, int x, int y, int color);
void	draw_player(t_config **data, int x, int y, int color);
void	draw(t_config **data);
void	free_doube_eraay(char **str);
void	destroy_data(t_config **data);
void	fontion_mlx_and_draw(t_config **data);
void	map_inistialisation(t_config **data);
void	chek_argument_and_extention(int err, char *map_name);
void	struct_instialisation(t_config **data, char *map_name);
void	fontion_mlx_and_draw(t_config **data);
void	get_height_map(t_config **data);
void	free_double_array(char **str);
char	*delet_newlin(char *str);
int		open_map(t_config **data);
void	error_intalis(t_config ** data);
int		close_window(t_config **data);
void	calcul_size(t_config **data);
void	draw_square(t_config **data, int x, int y, int color);
void	creat_img(t_config **data);
int		rgb_to_int(int red, int green, int blue);
#endif
