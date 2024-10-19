/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:18:40 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/19 11:55:04 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_intalis(t_config **data)
{
	ft_putstr_fd("Failed to initialize mlx.\n", 2);
	destroy_data(data);
	exit(1);
}

void	struct_instialisation(t_config *config, char *path)
{
	config->map = ft_calloc (1, sizeof(t_map));
	config->map->north_texture = NULL;
	config->map->south_texture = NULL;
	config->map->west_texture = NULL;
	config->map->east_texture = NULL;
	config->map->floor_color = NULL;
	config->map->ceiling_color = NULL;
	config->map->map_height = 0;
	config->config_count = 0;
	config->path = path;
	config->size = TILE_SIZE;
	config->p_d_count = 0;
}

void	open_fd(char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	if (*fd <= 0)
	{
		perror("open");
		exit(1);
	}
}

void	map_inistialisation(t_config *config, int *fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(*fd);
	if (!line)
	{
		ft_putstr_fd("empty map\n", 2);
		close (*fd);
		free(config->map);
		free(config);
		exit (1);
	}
	while (1)
	{
		if (!line)
			break ;
		config->map->map_height++;
		free(line);
		line = get_next_line(*fd);
	}
	close(*fd);
	open_fd(config->path, fd);
	config->maps = ft_calloc(config->map->map_height + 1, sizeof(char *));
	config->maps[config->map->map_height] = NULL;
	while (1)
	{
		config->maps[i] = get_next_line(*fd);
		if (!config->maps[i++])
			break ;
	}
	close(*fd);
}

void	init_fc(t_config *config, char *line, int i, char *fc_config)
{
	int		j;
	char	**tmp_map;

	j = 0;
	while (config->maps[i][j] == ' ' || config->maps[i][j] == '\t'
		|| config->maps[i][j] == 'F' || config->maps[i][j] == 'C')
		j++;
	tmp_map = ft_split(line + j, ',');
	if (check_line(tmp_map, line + j))
	{
		printf("Error\nCheck lines\n"); 
		exit(1);
	}
	if (fc_config[0] == 'F' && !config->map->floor_color)
		config->map->floor_color = init_color(tmp_map);
	else if (fc_config[0] == 'C' && !config->map->ceiling_color)
		config->map->ceiling_color = init_color(tmp_map);
	else if (config->map->floor_color || config->map->ceiling_color)
	{
		printf("Error\nDuplicated F || C\n"); 
		exit(1);
	}
	free_line(tmp_map);
}

void inial_textures(t_config *data)
{
	data->counter = 0;
	close(data->f);
	data->width_window = 1900;
	data->height_window = 1000;
	if (!(data->texture_north = mlx_load_png(data->map->north_texture)))
		error_intalis(&data);
	if (!(data->texture_west = mlx_load_png(data->map->west_texture)))
		error_intalis(&data);
	if (!(data->texture_south = mlx_load_png(data->map->south_texture)))
		error_intalis(&data);
	if (!(data->texture_east = mlx_load_png(data->map->east_texture)))
		error_intalis(&data);
	if (!(data->texture_open_dor = mlx_load_png("textures/open__dor.png")))
		error_intalis(&data);
	if (!(data->texture_close_dor = mlx_load_png("textures/close__door.png")))
		error_intalis(&data);
	if (!(data->texture_r = mlx_load_png("textures/1.png")))
		error_intalis(&data);
	if (!(data->texture_pa = mlx_load_png("textures/2.png")))
		error_intalis(&data);
	if (!(data->texture_toush = mlx_load_png("textures/toush.png")))
		error_intalis(&data);
	data->move_x = 0;
	data->move_y = 0;
	data->dor_x = -1;
	data->dor_y = -1;
	data->player.fov_rd = (FOV * M_PI) / 180;
	data->map->map_width = ft_strlen(data->map->map_buffer[0]);
	data->ceiling_color = rgb_to_hex(data->map->ceiling_color[0], data->map->ceiling_color[1],data->map->ceiling_color[2]);
	data->floor_color = rgb_to_hex(data->map->floor_color[0], data->map->floor_color[1], data->map->floor_color[2]);
}
void leaks(void)
{
	system("leaks cub3D");
}
int	main(int ac, char **av)
{
	t_config	*data;
	// atexit(leaks);
	data = ft_calloc(1, sizeof(t_config));
	if (!data)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit(1);
	}
	check_extenstion(av[1], ac);
	open_fd(av[1], &data->fd_map);
	struct_instialisation(data, av[1]);
	map_inistialisation(data, &data->fd_map);
	map_data_check(data);
	isolate_map_area(data);
	check_map(data);
	check_player(data);
	check_valid_map(data);
	inial_textures(data);
	if (!(data->mlx_ptr = mlx_init(data->width_window, data->height_window, "cub_3d", true)))
		error_intalis(&data);
	data->rays = ft_calloc(data->width_window, sizeof(t_ray));
	if (!data->rays)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		destroy_data(&data);
		exit(1);
	}
	fontion_mlx_and_draw(&data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}

