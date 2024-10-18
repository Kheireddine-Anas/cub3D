/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:26:09 by akheired          #+#    #+#             */
/*   Updated: 2024/10/18 12:00:17 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

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
char	*get_next_line(int fd);
char	**spliter(char *str);
char	**ft_split(char *s, char c);
void	*ft_calloc(size_t count, size_t size);
int		*init_color(char **tab);
void	check_extenstion(char *exe, int ac);
char	*ft_strjoin(char *holder, char *buff);
int		find_new_line(char *str);
char	*ft_first_line(char *first_str);
char	*ft_last_line(char *last_str);
void	check_colors(t_config *config);
void	check_extenstion(char *exe, int ac);
int		check_config(char **line, t_config **map);
int		check_line(char **tmp_map, char *line);
void	map_data_check(t_config *config);
void	check_valid_map(t_config *config);
void	check_map(t_config *config);
void	check_player(t_config *config);
void	check_space(t_config *config, int i, int j);
int		check_map_row_start(char *map_line);
int		skip_line(char *line);
void	free_line(char **line);
int		line_len(char **line);
void	set_directions(char **identifier, char *line);
void	init_fc(t_config *config, char *line, int i, char *fc_config);
int		check_chars(char *line);
void	isolate_map_area(t_config *config);
void	check_doors(char **map);
int		row(char *line);

#endif