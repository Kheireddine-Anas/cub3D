/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:15:14 by akheired          #+#    #+#             */
/*   Updated: 2024/08/16 09:09:58 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			break ;
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
			break ;
	}
	close(*fd);
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
		printf("Error\nDuplicated F || C\n"); 
		exit(1);
	}
	free_line(tmp_map);
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
	check_valid_map(&config);
	system("leaks cub3D");
}
