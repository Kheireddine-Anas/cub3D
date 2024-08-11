
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdlib.h>
# include <string.h>
# include "getNextLine/get_next_line_bonus.h"
# include "mlx/mlx.h"
# include <math.h>
#include "fcntl.h"

typedef struct s_config
{
	char	**map;
	char	*path;
	int		fd_map;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		*floor_color;
	int		*ceiling_color;
	int		counter;
	int		map_height;
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
}		t_config;

void	erroring(int err);
void	check_extenstion(char *exe, int ac);
void	parse_rgb(char *line, int *color);
void	parse_cub_file(char *filename, t_config *config);
int		find_new_line(char *str);
char	*ft_first_line(char *first_str);
char	*ft_last_line(char *last_str);
char	**spliter(char const *str);


#endif
