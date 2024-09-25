/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_distance_horizental.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:37:07 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/25 16:26:25 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_intersection(t_config *data, double xintercept, double Hintercept)
{
	int	mapGridIndexX;
	int	mapGridIndexY;

	if (xintercept < 0 || xintercept >= data->width_window || Hintercept < 0 || Hintercept >= data->height_window)
		return (0);
	mapGridIndexX = (int)floor(xintercept / data->size);
	mapGridIndexY = (int)floor(Hintercept / data->size);
	if (mapGridIndexX < 0 || mapGridIndexX >= data->map->map_width || mapGridIndexY < 0 || mapGridIndexY >= data->map->map_height)
		return (0);
	if (data->map->map_buffer[mapGridIndexY][mapGridIndexX] == '1' || data->map->map_buffer[mapGridIndexY][mapGridIndexX] == 'P' || data->map->map_buffer[mapGridIndexY][mapGridIndexX] == '4')
		return (0);
	return (1);
}

void initialize_variables(t_config **data)
{
	(*data)->ray.ray_ngl = normalizeAngle((*data)->ray.ray_ngl);
	(*data)->chek_orizental.isRayFacingDown = ((*data)->ray.ray_ngl > 0 && (*data)->ray.ray_ngl < M_PI);
	(*data)->chek_orizental.isRayFacingUp = !(*data)->chek_orizental.isRayFacingDown;
	(*data)->chek_orizental.isRayFacingRight = ((*data)->ray.ray_ngl < 0.5 * M_PI || (*data)->ray.ray_ngl > 1.5 * M_PI);
	(*data)->chek_orizental.isRayFacingLeft = !(*data)->chek_orizental.isRayFacingRight;
}

void calculate_intercepts_and_steps(t_config **data)
{
	double player_x;
	double player_y;

	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	(*data)->chek_orizental.Hintercept = floor((player_y / (*data)->size)) * (*data)->size;
	if ((*data)->chek_orizental.isRayFacingDown)
		(*data)->chek_orizental.Hintercept += (*data)->size;
	(*data)->chek_orizental.xintercept = player_x + ((*data)->chek_orizental.Hintercept - player_y) / tan((*data)->ray.ray_ngl);
	(*data)->chek_orizental.ystep = (*data)->size;
	if ((*data)->chek_orizental.isRayFacingUp)
		(*data)->chek_orizental.ystep *= -1;
	(*data)->chek_orizental.xstep = (*data)->size / tan((*data)->ray.ray_ngl);
	if (((*data)->chek_orizental.isRayFacingRight && (*data)->chek_orizental.xstep < 0) || ((*data)->chek_orizental.isRayFacingLeft && (*data)->chek_orizental.xstep > 0))
		(*data)->chek_orizental.xstep *= -1;
}

double check_horizontal(t_config **data, int i)
{
	initialize_variables(data);
	calculate_intercepts_and_steps(data);
	while ((*data)->chek_orizental.xintercept >= 0 && (*data)->chek_orizental.xintercept <= ((*data)->map->map_width * size_) &&
		   (*data)->chek_orizental.Hintercept >= 0 && (*data)->chek_orizental.Hintercept  <= ((*data)->map->map_height * size_))
	{
		(*data)->chek_orizental.xToCheck = (*data)->chek_orizental.xintercept;
		if ((*data)->chek_orizental.isRayFacingUp)
			(*data)->chek_orizental.yToCheck = (*data)->chek_orizental.Hintercept - 1;
		else
			(*data)->chek_orizental.yToCheck = (*data)->chek_orizental.Hintercept;
		if (!check_intersection(*data, (*data)->chek_orizental.xToCheck, (*data)->chek_orizental.yToCheck))
			break;
		else
		{
			(*data)->chek_orizental.xintercept += (*data)->chek_orizental.xstep;
			(*data)->chek_orizental.Hintercept += (*data)->chek_orizental.ystep;
		}
	}
	(*data)->ray.horiz_x = (*data)->chek_orizental.xToCheck;
	(*data)->ray.horiz_y = (*data)->chek_orizental.yToCheck;
	(*data)->rays[i].horiz_x = (*data)->chek_orizental.xToCheck;
	(*data)->rays[i].horiz_y = (*data)->chek_orizental.yToCheck;
	return (distanceBetweenPoints((*data)->player.x + (*data)->move_x, (*data)->player.y + (*data)->move_y, (*data)->chek_orizental.xintercept, (*data)->chek_orizental.Hintercept));
}
