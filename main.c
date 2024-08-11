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
	config->counter = 0;
	config->path = path;
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

void	map_data_check(t_config *config)
{
	skip_line(config->map);
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
	printf("PATH: %s\nMAP: %s\nHeight: %d", config.path, config.map[0], config.map_height);

}
