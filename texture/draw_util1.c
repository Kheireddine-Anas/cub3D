/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:22:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/28 21:45:47 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	calcul_size(t_config **data)
{
	int	cell_width;
	int	cell_height;

	if (!data || !(*data) || !(*data)->map)
		return ;
	cell_width = (*data)->width_window / (*data)->map->map_width;
	cell_height = (*data)->height_window /(*data)->map->map_height;
	if (cell_width < cell_height)
		(*data)->size = cell_width;
	else
		(*data)->size = cell_height;
}


void	draw_square(t_config **data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (*data)->size)
	{
		j = 0;
		while (j < (*data)->size)
		{
			mlx_put_pixel((*data)->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_config **data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_put_pixel((*data)->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	free_doube_eraay(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}