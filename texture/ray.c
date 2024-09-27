/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:33:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/26 14:02:27 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	normalizeangle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	if (angle > 2 * M_PI)
		angle = angle - (2 * M_PI);
	return (angle);
}

double	distancebetweenpoints(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

static void	if_condition(t_config **data, int ray)
{
	double	dis_vertical;
	double	dis_horizontal;

	(*data)->rays[ray].index = ray;
	dis_horizontal = check_horizontal(data, ray);
	dis_vertical = check_vertical(data, ray);
	if (dis_horizontal <= dis_vertical)
	{
		(*data)->ray.flag = 1;
		(*data)->rays[ray].flag = 1;
		(*data)->rays[ray].distance = dis_horizontal;
	}
	else
	{
		(*data)->ray.flag = 0;
		(*data)->rays[ray].flag = 0;
		(*data)->rays[ray].distance = dis_vertical;
	}
	render_wall(data, ray, (*data)->rays[ray].distance, (*data)->ray.ray_ngl);
}

void	castallrays(t_config **data)
{
	int		ray;
	double	player_x;
	double	player_y;

	(*data)->rays = ft_calloc((*data)->width_window, sizeof(t_ray));
	if (!(*data)->rays)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit(1);
	}
	ray = 0;
	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	(*data)->ray.ray_ngl = ((*data)->player.angle + (*data)->mouv_camera_left)
		- ((*data)->player.fov_rd / 2);
	(*data)->rays[ray].ray_ngl = (*data)->ray.ray_ngl;
	while (ray <= (*data)->width_window)
	{
		if_condition(data, ray);
		(*data)->ray.ray_ngl += ((*data)->player.fov_rd
				/ (*data)->width_window);
		ray++;
		(*data)->rays[ray].ray_ngl = (*data)->ray.ray_ngl;
	}
}
