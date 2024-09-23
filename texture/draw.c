/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:45:00 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/23 13:47:42 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	determine_engle(t_config **data, int i, int j)
{
	if ((*data)->map->map_buffer[i][j] == 'E')
		(*data)->player.angle = 0;
	if ((*data)->map->map_buffer[i][j] == 'N')
		(*data)->player.angle = 90;
	if ((*data)->map->map_buffer[i][j] == 'W')
		(*data)->player.angle = 180;
	if ((*data)->map->map_buffer[i][j] == 'S')
		(*data)->player.angle = 270;
}


void	while_(t_config **data, int i, int *j)
{
	int	x;
	int	y;
	while ((*data)->map->map_buffer[i][*j])
	{
		x = *j * (*data)->size;
		y = i * (*data)->size;
		if ((*data)->map->map_buffer[i][*j] == 'N'
			|| (*data)->map->map_buffer[i][*j] == 'S'
			|| (*data)->map->map_buffer[i][*j] == 'W'
			|| (*data)->map->map_buffer[i][*j] == 'E')
		{
			(*data)->player.x = x;
			(*data)->player.y = y;
			determine_engle(data, i, *j);
		}
		(*j)++;
	}
}

void	draw_line(t_config *data, double x0, double y0, double x1, double y1,
		int color)
{
	double		x_step;
	double		y_step;
	double		max;
	double		abs_x_step;
	double		abs_y_step;
	if (data == NULL  || data->map == NULL
		|| data->map->map_buffer == NULL)
		error_intalis(&data);
	x_step = x1 - x0;
	y_step = y1 - y0;
	abs_x_step = fabs(x_step);
	abs_y_step = fabs(y_step);
	max = fmaxf(abs_x_step, abs_y_step);
	x_step /= max;
	y_step /= max;
	while ((x_step > 0 && x0 <= x1)
		|| (x_step < 0 && x0 >= x1)
		|| (y_step > 0 && y0 <= y1)
		|| (y_step < 0 && y0 >= y1))
	{
		if (x0 > 0 && x0  < data->width_window && y0 > 0 && y0 < data->height_window)
			mlx_put_pixel(data->img, (int)x0, (int)y0, color);
		x0 += x_step;
		y0 += y_step;
	}
}

void	draw(t_config **data,  mlx_texture_t *texture)
{
	int	i;
	int	j;

	if (!((*data)->img = mlx_new_image((*data)->mlx_ptr, (*data)->width_window, (*data)->height_window)))
		error_intalis(data);
	i = 0;
	(*data)->size = TILE_SIZE;
	while ((*data)->map->map_buffer[i])
	{
		j = 0;
		while_(data, i, &j);
		i++;
	}
	castAllRays(data);
	draw_minimap(data);
	draw_centered_image(*data, texture);
	if (mlx_image_to_window((*data)->mlx_ptr, (*data)->img, 0, 0) == -1)
		error_intalis(data);
}

void draw_update(t_config **data, mlx_texture_t *texture)
{
	if (!((*data)->img = mlx_new_image((*data)->mlx_ptr, (*data)->width_window, (*data)->height_window)))
		error_intalis(data);
	castAllRays(data);
	draw_minimap(data);
	draw_centered_image(*data, texture);
	if (mlx_image_to_window((*data)->mlx_ptr, (*data)->img, 0, 0) == -1)
		error_intalis(data);
}
