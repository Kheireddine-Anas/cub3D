/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:45:00 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/19 10:00:05 by ahamdi           ###   ########.fr       */
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
		else if ((*data)->map->map_buffer[i][*j] == 'N'
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

void	draw_line(t_config **data, int x0, int y0, double x1, double y1,
		int color)
{
	int	map_width;
	int	map_height;
	int	size;
	int	deltaX;
	int	deltaY;
	int	signX;
	int	signY;
	int	error;
	int	map_x;
	int	map_y;
	int	error2;

	if (data == NULL || *data == NULL || (*data)->map == NULL
		|| (*data)->map->map_buffer == NULL)
		error_intalis(data);
	map_width = (*data)->map->map_width;
	map_height = (*data)->map->map_height;
	size = (*data)->size;
	deltaX = fabs(x1 - x0);
	deltaY = fabs(y1 - y0);
	signX = x0 < x1 ? 1 : -1;
	signY = y0 < y1 ? 1 : -1;
	error = deltaX - deltaY;
	while (x0 != x1 || y0 != y1)
	{
		map_x = x0 / size;
		map_y = y0 / size;
		if ((*data)->map->map_buffer[map_y][map_x] == '1')
			break ;
		mlx_put_pixel((*data)->img, x0, y0, color);
		error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x0 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y0 += signY;
		}
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

	player_x = (*data)->player.x + (*data)->mouve_palyer_left;
	player_y = (*data)->player.y + (*data)->mouve_palyer_haut;
	(*data)->player.angle += (*data)->mouv_camera_left;
	end_angle = (*data)->player.angle + FOV / 2;
	ray_angle = (*data)->player.angle - FOV / 2;
	while (ray_angle <= end_angle)
	{
		ray_x = player_x + (*data)->height_window * cos(ray_angle);
		ray_y = player_y + (*data)->height_window * sin(ray_angle);
		draw_line(data, player_x, player_y, ray_x, ray_y, 0xFFFFFF);
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
	// draw_player(data, (*data)->player.x + (*data)->mouve_palyer_left,
	// 	(*data)->player.y + (*data)->mouve_palyer_haut, 0xFF000000);
	draw_player_rays(data);
	if (mlx_image_to_window((*data)->mlx_ptr, (*data)->img, 0, 0) == -1)
		error_intalis(data);
}
