/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:33:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/25 15:51:07 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	normalizeAngle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

double	distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	castAllRays(t_config **data)
{
	double	dis_vertical;
	double	dis_horizontal;
	int		ray;
	double	dis;
	double	player_x;
	double	player_y;

	(*data)->rays = ft_calloc((*data)->width_window, sizeof(t_ray));
	if (!(*data)->rays)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit (1);
	}
	ray = 0;
	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	(*data)->ray.ray_ngl = ((*data)->player.angle + (*data)->mouv_camera_left)
		- ((*data)->player.fov_rd / 2);
	(*data)->rays[ray].ray_ngl = (*data)->ray.ray_ngl;
	while (ray <= (*data)->width_window)
	{
		(*data)->rays[ray].index = ray;
		dis_horizontal = check_horizontal(data, ray);
		dis_vertical = check_vertical(data, ray);
		if (dis_horizontal <= dis_vertical)
		{
			(*data)->ray.flag = 1;
			(*data)->rays[ray].flag = 1;
			dis = dis_horizontal;
		}
		else
		{
			(*data)->ray.flag = 0;
			(*data)->rays[ray].flag = 0;
			dis = dis_vertical;
		}
		(*data)->rays[ray].distance = dis;
		render_wall(data, ray, dis, (*data)->ray.ray_ngl);
		(*data)->ray.ray_ngl += ((*data)->player.fov_rd
				/ (*data)->width_window);
		ray++;
		(*data)->rays[ray].ray_ngl = (*data)->ray.ray_ngl;
	}
}


void	chek_door(t_config **data)
{
	int i;
	int map_y;
	int map_x;

	i = 0;
	(*data)->dor_x = -1;
	(*data)->dor_y = -1;
	while (i < (*data)->width_window)
	{
		if ((*data)->rays[i].flag == 1)
		{
			map_y = (int)((*data)->rays[i].horiz_y / TILE_SIZE);
    		map_x = (int)((*data)->rays[i].horiz_x / TILE_SIZE);
			if ( (*data)->rays[i].distance <= 50 &&
       			map_y >= 0 && map_y < (*data)->map->map_height && // Vérifiez la hauteur de la carte
        		(*data)->map->map_buffer[map_y] &&
        		map_x >= 0 && map_x < (*data)->map->map_width && // Vérifiez la largeur de la carte
        		((*data)->map->map_buffer[map_y][map_x] == 'P' || (*data)->map->map_buffer[map_y][map_x] == '4'))
        	{
				(*data)->dor_x = map_x;
				(*data)->dor_y = map_y;
				return ;
			}
		}
		else
		{
			map_y = (int)((*data)->rays[i].vert_y / TILE_SIZE);
    		map_x = (int)((*data)->rays[i].vert_x / TILE_SIZE);
			if ( (*data)->rays[i].distance <= 50 &&
       			map_y >= 0 && map_y < (*data)->map->map_height && // Vérifiez la hauteur de la carte
        		(*data)->map->map_buffer[map_y] &&
        		map_x >= 0 && map_x < (*data)->map->map_width && // Vérifiez la largeur de la carte
        		((*data)->map->map_buffer[map_y][map_x] == 'P' || (*data)->map->map_buffer[map_y][map_x] == '4'))
        	{
				(*data)->dor_x = map_x;
				(*data)->dor_y = map_y;
				return ;
			}
		}
		i++;
	}
}
