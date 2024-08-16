/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:28:16 by akheired          #+#    #+#             */
/*   Updated: 2024/08/16 08:54:47 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_extenstion(char *exe, int ac)
{
	int	i;

	i = 0;
	if (ac != 2)
	{
		printf("Error\nCheck the number of args\n");
		exit(1);
	}
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

int	check_config(char **line, t_config **map)
{
	if (line_len(line) == 2 && (!ft_strcmp(line[0], "NO")
			|| !ft_strcmp(line[0], "SO") || !ft_strcmp(line[0], "WE")
			|| !ft_strcmp(line[0], "EA")))
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
	if (!ft_strcmp(line[0], "F") || !ft_strcmp(line[0], "C"))
	{
		(*map)->config_count++;
		return (0);
	}
	return (1);
}

void	map_data_check(t_config *config)
{
	int		i;
	char	**line;

	i = -1;
	while (config->map[++i])
	{
		if (skip_line(config->map[i]))
			continue ;
		line = spliter(config->map[i]);
		if (check_config(line, &config) && config->config_count < 6)
		{
			printf("Error\nInvalide Config\n");
			exit(33);
		}
		if (!ft_strcmp(line[0], "F") || !ft_strcmp(line[0], "C"))
			init_fc(config, config->map[i], i, line[0]);
		free_line(line);
	}
	check_colors(config);
}

void	check_valid_map(t_config *config)
{
	int	i;
	int	j;

	i = -1;
	while (config->cp_map[++i])
	{
		j = -1;
		while (config->cp_map[i][++j] != '\n' && config->cp_map[i][j] != '\0')
		{
			if (config->cp_map[i][j] == '0' || config->cp_map[i][j] == 'W'
				|| config->cp_map[i][j] == 'D' || config->cp_map[i][j] == 'N'
				|| config->cp_map[i][j] == 'S')
				check_space(config, i, j);
		}
	}
}
