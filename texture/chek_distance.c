/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:37:07 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/19 11:16:27 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_intersection(t_config *data, double xintercept, double Hintercept)
{
	int	mapGridIndexX;
	int	mapGridIndexY;

	if (xintercept < 0 || xintercept >= data->width_window || Hintercept < 0
		|| Hintercept >= data->height_window)
		return (0);
	mapGridIndexX = (int)floor(xintercept / data->size);
	mapGridIndexY = (int)floor(Hintercept / data->size);
	if (mapGridIndexX < 0 || mapGridIndexX >= data->map->map_width
		|| mapGridIndexY < 0 || mapGridIndexY >= data->map->map_height)
		return (0);
	if (data->map->map_buffer[mapGridIndexY][mapGridIndexX] == '1' || data->map->map_buffer[mapGridIndexY][mapGridIndexX] == 'P' || data->map->map_buffer[mapGridIndexY][mapGridIndexX] == '4' ||data->map->map_buffer[mapGridIndexY][mapGridIndexX] == 'K')
		return (0);
	return (1);
}

double check_horizontal(t_config **data, double rayAngle, int i)
{
    int isRayFacingDown;
    int isRayFacingUp;
    int isRayFacingRight;
    int isRayFacingLeft;
    double xintercept;
    double Hintercept;
    double xstep;
    double player_x;
    double player_y;
    double ystep;
    double nextHorzTouchX;
    double nextHorzTouchY;
    double xToCheck;
    double yToCheck;

    rayAngle = normalizeAngle(rayAngle);
    player_x = (*data)->player.x + (*data)->move_x;
    player_y = (*data)->player.y + (*data)->move_y;

    isRayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
    isRayFacingUp = !isRayFacingDown;
    isRayFacingRight = (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI);
    isRayFacingLeft = !isRayFacingRight;

    Hintercept = floor(player_y / (*data)->size) * (*data)->size;
    if (isRayFacingDown)
        Hintercept += (*data)->size;
    xintercept = player_x + (Hintercept - player_y) / tan(rayAngle);
    ystep = (*data)->size;
    if (isRayFacingUp)
        ystep *= -1;
    xstep = (*data)->size / tan(rayAngle);
    if ((isRayFacingRight && xstep < 0) || (isRayFacingLeft && xstep > 0))
        xstep *= -1;

    nextHorzTouchX = xintercept;
    nextHorzTouchY = Hintercept;

    while (nextHorzTouchX >= 0 && nextHorzTouchX <= (*data)->width_window &&
           nextHorzTouchY >= 0 && nextHorzTouchY <= (*data)->height_window)
    {
        xToCheck = nextHorzTouchX;
        yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0); // Ajustement pour les rayons se dirigeant vers le haut

        if (!check_intersection(*data, xToCheck, yToCheck))
            break;
        else 
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }
    (*data)->ray.horiz_x = xToCheck;
    (*data)->ray.horiz_y =  yToCheck;
    (*data)->rays[i].horiz_x = xToCheck;
    (*data)->rays[i].horiz_y = yToCheck;
    return distanceBetweenPoints(player_x, player_y, nextHorzTouchX, nextHorzTouchY);
}
double check_vertical(t_config **data, double rayAngle, int i)
{
    int isRayFacingDown;
    int isRayFacingUp;
    int isRayFacingRight;
    int isRayFacingLeft;
    double Vintercept;
    double yintercept;
    double xstep;
    double player_x;
    double player_y;
    double ystep;
    double nextVertTouchX;
    double nextVertTouchY;
    double xToCheck;
    double yToCheck;

    rayAngle = normalizeAngle(rayAngle);
    player_x = (*data)->player.x + (*data)->move_x;
    player_y = (*data)->player.y + (*data)->move_y;

    isRayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
    isRayFacingUp = !isRayFacingDown;
    isRayFacingRight = (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI);
    isRayFacingLeft = !isRayFacingRight;

    // Calcul des intercepts verticaux
    Vintercept = floor(player_x / (*data)->size) * (*data)->size;
    if (isRayFacingRight)
        Vintercept += (*data)->size;
    yintercept = player_y + (Vintercept - player_x) * tan(rayAngle);

    xstep = (*data)->size;
    if (isRayFacingLeft)
        xstep *= -1;

    ystep = (*data)->size * tan(rayAngle);
    if (isRayFacingUp && ystep > 0)
        ystep *= -1;
    if (isRayFacingDown && ystep < 0)
        ystep *= -1;

    nextVertTouchX = Vintercept;
    nextVertTouchY = yintercept;

    while (nextVertTouchX >= 0 && nextVertTouchX <= (*data)->width_window &&
           nextVertTouchY >= 0 && nextVertTouchY <= (*data)->height_window)
    {
        xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0); // Ajustement pour les rayons se dirigeant vers la gauche
        yToCheck = nextVertTouchY;

        if (!check_intersection(*data, xToCheck, yToCheck))
            break;
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }
    (*data)->ray.vert_x =    xToCheck;
    (*data)->ray.vert_y =     yToCheck;
     (*data)->rays[i].vert_x =    xToCheck;
    (*data)->rays[i].vert_y =    yToCheck;
    return (distanceBetweenPoints(player_x, player_y, nextVertTouchX, nextVertTouchY));
}