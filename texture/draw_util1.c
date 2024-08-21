/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:22:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/19 12:14:06 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int rgb_to_int(int red, int green, int blue)
{
    if (red < 0) red = 0; else if (red > 255) red = 255;
    if (green < 0) green = 0; else if (green > 255) green = 255;
    if (blue < 0) blue = 0; else if (blue > 255) blue = 255;
    return (red << 16) | (green << 8) | blue;
}


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

void	my_mlx_pixel_put(t_config **data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 1300 || y >= 1300)
		return ;
	dst = (*data)->addr + (y * (*data)->line_length + 
			x * ((*data)->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
