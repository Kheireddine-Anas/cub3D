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
int	close_window(t_config **data)
{
	mlx_destroy_window((*data)->mlx_ptr, (*data)->win_ptr);
	mlx_destroy_image((*data)->mlx_ptr, (*data)->img);
	ft_putstr_fd(" close window", 1);
	// free_3d_char_array(data);
	free(*data); 
	exit(0); 
}
void	fontion_mlx_and_draw(t_config **data)
{
	// mlx_key_hook((*data)->win_ptr, key_press, data);
	mlx_hook((*data)->win_ptr, 17, 0, close_window, data);
}
void	initial_data(t_config **data, char **argv)
{
	(void)argv;
	(*data)->width_window = 1300;
	(*data)->height_window = 1300;
}
void	error_intalis(t_config **data)
{
	ft_putstr_fd("Failed to initialize mlx.\n", 2);
	free(data);
	exit (1);
}
int	main(int ac, char **av)
{
	// int			fd;
	t_config	*data;
	(void)ac;
	// check_extenstion(av[1], ac);
	// open_fd(av[1], &fd);
	// struct_instialisation(&data, av[1]);
	// map_inistialisation(&data, &fd);
	data = (t_config *)malloc(sizeof(t_config));
	data->mlx_ptr = mlx_init();
	initial_data(&data, av);
	if (data->mlx_ptr == NULL)
		error_intalis(&data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width_window,
			data->height_window, "CUB3D project");
	if (data->win_ptr == NULL)
		error_intalis(&data);
	data->img = mlx_new_image(data->mlx_ptr, 1300, 1300);
	if (!data->img)
		error_intalis(&data);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
			&data->line_length, &data->endian);
	fontion_mlx_and_draw(&data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

