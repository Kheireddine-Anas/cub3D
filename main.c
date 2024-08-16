# include "cub3d.h"

void	erroring(int err)
{
	if (err == 1)
		printf("Error\nCheck the number of args\n");
	exit(1);
}
void	check_extenstion(char *exe, int ac)
{
	int	i;

	i = 0;
	if (ac != 2)
		erroring(1);
	while (exe[i])
		i++;
	if (!(exe[i - 5]) || exe[i - 4] != '.' || exe[i - 3] != 'c'
		|| exe[i - 2] != 'u' || exe[i - 1] != 'b')
	{
		write(1, "Error\n", 7);
		write(1, "Map Extention Map.cub\n", 23);
		exit(1);
	}
}

void	struct_instialisation(t_config *config, char *path)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->floor_color = NULL;
	config->ceiling_color = NULL;
	config->map_height = 0;
	config->config_count = 0;
	config->path = path;
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
	while (1)
	{
		line = get_next_line(*fd);
		if (!line)
			break;
		config->map_height++;
		free(line);
	}
	close(*fd);
	open_fd(config->path, fd);
	config->map = ft_calloc(config->map_height + 1, sizeof(char *));
	config->map[config->map_height] = NULL;
	while (1)
	{
		config->map[i] = get_next_line(*fd);
		if (!config->map[i++])
			break;
	}
	close(*fd);
}

int	skip_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i] || line[i] == '\n')
		return (1);
	return (0);
}

void	free_line(char **line)
{
	int	i;

	i = -1;
	while (line[++i])
		free(line[i]);
	free(line);
}

int	line_len(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	check_line(char **tmp_map, char *line)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (line[++i])
		if (line[i] == ',')
			j++;
	if (j != 2)
		return (1);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		|| line[i] == ',' || (line[i] >= '0' && line[i] <= '9'))
		i++;
	if (line[i] != '\0')
		return (1);
	if (line_len(tmp_map) != 3)
		return (1);
	return (0);
}

void	init_fc(t_config *config, char *line, int i, char *fc_config)
{
	int		j;
	char	**tmp_map;

	j = 0;
	while (config->map[i][j] == ' ' || config->map[i][j] == '\t'
		|| config->map[i][j] == 'F' || config->map[i][j] == 'C')
		j++;
	tmp_map = ft_split(line + j, ',');
	if (check_line(tmp_map, line + j))
	{
		printf("Error\nCheck lines\n"); 
		exit(1);
	}
	if (fc_config[0] == 'F' && !config->floor_color)
		config->floor_color = init_color(tmp_map);
	else if (fc_config[0] == 'C' && !config->ceiling_color)
		config->ceiling_color = init_color(tmp_map);
	else if (config->floor_color || config->ceiling_color)
	{
		printf("Duplicated F || C\n"); 
		exit(1);
	}
	free_line(tmp_map);
}

void	set_directions(char **identifier, char *line)
{
	if (*identifier != NULL)
	{
		printf("Error\nDuplicated Path Directions\n");
		exit(12);
	}
	*identifier = ft_strdup(line);
}

int	check_config(char **line, t_config **map)
{
	if (line_len(line) == 2 && (!ft_strcmp(line[0], "NO") || !ft_strcmp(line[0], "SO")
		|| !ft_strcmp(line[0], "WE") || !ft_strcmp(line[0], "EA")))
	{
		if (!ft_strcmp(line[0], "NO"))
			set_directions(&(*map)->north_texture, line[1]);
		else if (!ft_strcmp(line[0], "SO"))
			set_directions(&(*map)->south_texture, line[1]);
		else if (!ft_strcmp(line[0], "WE"))
			set_directions(&(*map)->west_texture, line[1]);
		else if (!ft_strcmp(line[0], "EA"))
			set_directions(&(*map)->east_texture, line[1]);
		(*map)->config_count++;
		return (0);
	}
	if(!ft_strcmp(line[0], "F") || !ft_strcmp(line[0], "C"))
	{
		(*map)->config_count++;
		return (0);
	}
	return (1);
}

void	check_colors(t_config *config)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (config->floor_color[i] < 0 || config->floor_color[i] > 255
			|| config->ceiling_color[i] < 0 || config->ceiling_color[i] > 225)
		{
			printf("Error\nCheck Colors range\n");
			exit(1);
		}	
	}
}

void	map_data_check(t_config *config)
{
	int		i;
	char	**line;

	i = -1;
	while (config->map[++i])
	{
		if (skip_line(config->map[i]))
			continue;
		line = spliter(config->map[i]);
		if (check_config(line, &config) && config->config_count < 6)
		{
			printf("Error\nInvalide Config\n");
			exit(33);
		}
		if (!ft_strcmp(line[0], "F") || !ft_strcmp(line[0], "C"))
			init_fc(config, config->map[i], i, line[0]);
		free_line(line); //Freeing Lines
	}
	check_colors(config);
}
int	check_map_row_start(char *map_line)
{
	int	i;

	i = 0;
	while (map_line[i] == ' ' || map_line[i] == '\t')
		i++;
	if (map_line[i] == '0' || map_line[i] == '1')
		return (1);
	return (0);
}

void	isolate_map_area(t_config *config)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (config->map[++i])
		if (check_map_row_start(config->map[i]))
			break ;
	while (config->map[--config->map_height] && config->map_height > i)
		if (check_map_row_start(config->map[config->map_height]))
			break ;
	config->map_size = config->map_height - i + 1;
	config->cp_map = ft_calloc(config->map_size + 1, sizeof(char *));
	while (++j < config->map_height - i + 1)
		config->cp_map[j] = ft_strdup(config->map[i + j]);
	config->cp_map[j] = NULL;
	free_line(config->map);
}

int	check_chars(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != ' ' && line[i] != '\n' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'W' && line[i] != 'D'
			&& line[i] != 'N' && line[i] != 'S')
		return (1);
	return (0);
}

void	check_map(t_config *config)
{
	int i;

	i = -1;
	while (config->cp_map[++i])
	{
		if (skip_line(config->cp_map[i]))
		{
			printf("Error\nEmpty Line\n");
			exit(1);
		}
		if (check_chars(config->cp_map[i]))
		{
			printf("Error\nCheck Characters\n");
			exit(1);
		}
	}
}

void	check_player(t_config *config)
{
	int	i;
	int	j;

	i = -1;
	while (config->cp_map[++i])
	{
		j = -1;
		while (config->cp_map[i][++j])
		{
			if (config->cp_map[i][j] == 'N' || config->cp_map[i][j] == 'E'
				|| config->cp_map[i][j] == 'S' || config->cp_map[i][j] == 'W')
			{
				config->player_direction = config->cp_map[i][j];
				config->player_x = i;
				config->player_y = j;
				config->p_d_count++;
			}
		}
	}
	if (config->p_d_count != 1)
	{
		printf("Error\nNo more one player\n");
		exit(1);
	}
}

int	main(int ac, char **av)
{
	int			fd;
	t_config	config;

	check_extenstion(av[1], ac);
	open_fd(av[1], &fd);
	struct_instialisation(&config, av[1]);
	map_inistialisation(&config, &fd);
	map_data_check(&config);
	isolate_map_area(&config);
	check_map(&config);
	check_player(&config);
	system("leaks cub3D");
	// printf("PATH: %s\nMAP: %s\nHeight: %d", config.path, config.cp_map[0], config.map_height);
}
