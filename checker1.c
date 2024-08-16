/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:56:03 by akheired          #+#    #+#             */
/*   Updated: 2024/08/16 09:11:35 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_space(t_config *config, int i, int j)
{
	if (i == 0 || j == 0 || i == config->map_size - 1
		|| j == row(config->cp_map[i]) - 1 || config->cp_map[i + 1][j] == ' '
		|| config->cp_map[i - 1][j] == ' ' || config->cp_map[i][j + 1] == ' '
		|| config->cp_map[i][j - 1] == ' ')
	{
		printf("Error\nInvalide Map!\n");
		exit(1);
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

void	check_map(t_config *config)
{
	int	i;

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
