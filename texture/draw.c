/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:45:00 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/28 23:23:45 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_data(t_config **data)
{
	free_doube_eraay((*data)->map->map_buffer);
	free((*data)->map->north_texture);
	free((*data)->map->west_texture);
	free((*data)->map->south_texture);
	free((*data)->map->east_texture);
	free((*data)->map->floor_color);
	free((*data)->map->ceiling_color);
	free((*data)->map);
	free(*data);
}

int	close_window(t_config **data)
{
	if ((*data)->mlx_ptr && (*data)->img)
	{
		mlx_close_window((*data)->mlx_ptr);
	}
	ft_putstr_fd(" close window\n", 1);
	destroy_data(data);
	exit(0);
}
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
		if ((*data)->map->map_buffer[i][*j] == '1')
			draw_square(data, x, y, 0xFF0000FF);
		else if ((*data)->map->map_buffer[i][*j] == '0')
			draw_square(data, x, y, 0x02f7b2);
		if ((*data)->map->map_buffer[i][*j] == 'N'
			|| (*data)->map->map_buffer[i][*j] == 'S'
			|| (*data)->map->map_buffer[i][*j] == 'W'
			|| (*data)->map->map_buffer[i][*j] == 'E')
		{
			(*data)->player.x = x;
			(*data)->player.y = y;
			determine_engle(data, i, *j);
			draw_square(data, x, y, 0x02f7b2);
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

void	draw_player_rays(t_config **data)
{
	int		player_x;
	int		player_y;
	double	ray_angle;
	double	end_angle;
	double ray_x;
	double	ray_y;

	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	end_angle = ((*data)->player.angle + (*data)->mouv_camera_left) + FOV / 2;
	ray_angle = ((*data)->player.angle + (*data)->mouv_camera_left)  -  FOV / 2;
	while (ray_angle <= end_angle)
	{
		ray_x = player_x + 10 * cos(ray_angle);
		ray_y = player_y + 10 * sin(ray_angle);
		draw_line(*data, player_x, player_y, ray_x, ray_y, 0xFFFFFF);
		ray_angle += RAY_STEP;
	}
}
void	draw(t_config **data)
{
	int	i;
	int	j;

	if (!((*data)->img = mlx_new_image((*data)->mlx_ptr, (*data)->width_window, (*data)->height_window)))
		error_intalis(data);
	calcul_size(data);
	i = 0;
	while ((*data)->map->map_buffer[i])
	{
		j = 0;
		while_(data, i, &j);
		i++;
	}
	draw_player(data, (*data)->player.x + (*data)->move_x,
		(*data)->player.y + (*data)->move_y, 0xFF000000);
	castAllRays(*data);
	if (mlx_image_to_window((*data)->mlx_ptr, (*data)->img, 0, 0) == -1)
		error_intalis(data);
}
