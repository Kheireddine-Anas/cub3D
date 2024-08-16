/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:03:26 by akheired          #+#    #+#             */
/*   Updated: 2024/08/16 09:11:44 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
