/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:03:26 by akheired          #+#    #+#             */
/*   Updated: 2024/10/20 19:30:58 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	isolate_map_area(t_config *config)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (config->maps[++i])
		if (check_map_row_start(config->maps[i]))
			break ;
	while (config->maps[--config->map->map_height] 
		&& config->map->map_height > i)
		if (check_map_row_start(config->maps[config->map->map_height]))
			break ;
	config->map_size = config->map->map_height - i + 1;
	config->map->map_buffer = ft_calloc(config->map_size + 1, sizeof(char *));
	while (++j < config->map->map_height - i + 1)
		config->map->map_buffer[j] = ft_strdup(config->maps[i + j]);
	config->map->map_buffer[j] = NULL;
	free_line(config->maps);
}

int	row(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	while (line[--i] != ' ')
		;
	return (i + 1);
}

void	check_doors(char **map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j] != '\n' && map[i][j] != '\0')
		{
			if (map[i][j] == 'D')
			{
				if ((map[i][j - 1] != '1' || map[i][j + 1] != '1') 
					&& (map[i - 1][j] != '1' || map[i + 1][j] != '1'))
				{
					printf("Error\nCheck Doors\n");
					exit (1);
				}
			}
		}
	}
}

void	error_invalid(void)
{
	ft_putstr_fd("invalid map\n", 2);
	exit (1);
}
