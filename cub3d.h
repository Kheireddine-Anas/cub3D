// #ifndef CUB3D_H
// # define CUB3D_H

// # include <stdio.h>
// # include <fcntl.h>
// # include <mlx.h>
// # include <unistd.h>
// # include <stdlib.h>

// #endif

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

typedef struct s_config
{
	char	**map;
	char	**cp_map;
	char	*path;
	int		fd_map;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		*floor_color;
	int		*ceiling_color;
	int		config_count;
	int		map_height;
	int		map_size;
	int		player_x;
	int		player_y;
	int		player_direction;
	int		p_d_count;
}		t_config;

int		ft_strcmp(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_strdup(char *s);
char	*ft_substr(char *s, int start, int len);
char	*get_next_line(int fd); // Assuming you have implemented this function
char	**spliter(char *str);
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
int		*init_color(char **tab);
//GPTER
void	erroring(int err);
void	check_extenstion(char *exe, int ac);
void	parse_rgb(char *line, int *color);
void	parse_cub_file(char *filename, t_config *config);
char	*ft_strjoin(char *holder, char *buff);
int		find_new_line(char *str);
char	*ft_first_line(char *first_str);
char	*ft_last_line(char *last_str);



#endif
