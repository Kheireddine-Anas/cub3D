/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1_chek_and_initialis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:40:58 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/24 12:35:34 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	chek_argument_and_extention(int err, char *map_name)
{
	char	*str;

	if (err != 2)
	{
		ft_putstr_fd("Usage: ./cup <mapname>\n", 2);
		exit(1);
	}

	str = ft_strrchr(map_name, '.');
	if (!str || ft_strlen(str) != 4 || ft_strncmp(str, ".cub", 4) != 0)
	{
		ft_putstr_fd("invalid map\n", 2);
		exit(1);
	}
}


void	struct_instialisation(t_config **data, char *map_name)
{
	(*data)->map = ft_calloc(1, sizeof(t_config));
	(*data)->map->north_texture = NULL;
	(*data)->map->map_width = 0;
	(*data)->map->map_height = 0;
	(*data)->map->south_texture = NULL;
	(*data)->map->west_texture = NULL;
	(*data)->map->east_texture = NULL;
	(*data)->map->floor_color = NULL;
	(*data)->map->ceiling_color = NULL;
	(*data)->counter = 0;
	(*data)->map_name = map_name;
	(*data)->width_window = 1900;
	(*data)->height_window = 1000;
	(*data)->texture_or = mlx_load_png("textures/seamless_stone.png");
	(*data)->texture_ver = mlx_load_png("textures/seamless_stone.png");
	(*data)->texture_close_dor = mlx_load_png("textures/close__door.png");
	(*data)->texture_open_dor = mlx_load_png("textures/open__dor.png");
	(*data)->texture_r = mlx_load_png("textures/1.png");
	(*data)->texture_pa = mlx_load_png("textures/2.png");
	(*data)->texture_s = mlx_load_png("sprite/1.png");
	(*data)->texture_toush = mlx_load_png("textures/toush.png");
	(*data)->player.x = 0;
	(*data)->player.y = 0;
	(*data)->player.angle = 0;
	(*data)->move_x = 0;
	(*data)->move_y = 0;
	(*data)->f = 0;
	(*data)->size = 0;
	(*data)->dor_x = -1;
	(*data)->dor_y = -1;
	(*data)->player.fov_rd = (FOV * M_PI) / 180;
}

void	free_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*delet_newlin(char *str)
{
	int		i;
	char	*s;
	int		j;

	j = 0;
	i = 0;
	s = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] != '\n')
			s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}

int	open_map(t_config **data)
{
	int	fd;

	fd = open((*data)->map_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Failed to open the file.\n", 2);
		free(*data);
		exit(1);
	}
	return (fd);
}
