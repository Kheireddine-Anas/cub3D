/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_distance_mini_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:37:07 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/30 16:49:22 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
int	check_intersection_mini(t_config *data, double xintercept, double Hintercept)
{
	int	mapGridIndexX;
	int	mapGridIndexY;

	if (xintercept < 0 || xintercept >= data->width_window || Hintercept < 0
		|| Hintercept >= data->height_window)
		return (0);
	mapGridIndexX = (int)floor(xintercept / size_);
	mapGridIndexY = (int)floor(Hintercept / size_);
	if (mapGridIndexX < 0 || mapGridIndexX >= data->map->map_width
		|| mapGridIndexY < 0 || mapGridIndexY >= data->map->map_height)
		return (0);
	if (data->map->map_buffer[mapGridIndexY][mapGridIndexX] == '1')
		return (0);
	return (1);
}
double check_horizontal_mini(t_config *data, double rayAngle)
{
    int isRayFacingDown;
    int isRayFacingUp;
    int isRayFacingRight;
    int isRayFacingLeft;
    double xintercept;
    double Hintercept;
    double xstep;
    int player_x;
    int player_y;
    double ystep;
    double nextHorzTouchX;
    double nextHorzTouchY;
    double xToCheck;
    double yToCheck;

    rayAngle = normalizeAngle(rayAngle);
    player_x = data->player.x_mini + data->move_x_min;
    player_y = data->player.y_mini + data->move_y_min;

    isRayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
    isRayFacingUp = !isRayFacingDown;
    isRayFacingRight = (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI);
    isRayFacingLeft = !isRayFacingRight;
    Hintercept = floor(player_y / size_) * size_;
    if (isRayFacingDown)
        Hintercept += size_;
    xintercept = player_x + (Hintercept - player_y) / tan(rayAngle);
    ystep = size_;
    if (isRayFacingUp)
        ystep *= -1;
    xstep = size_ / tan(rayAngle);
    if ((isRayFacingRight && xstep < 0) || (isRayFacingLeft && xstep > 0))
        xstep *= -1;

    nextHorzTouchX = xintercept;
    nextHorzTouchY = Hintercept;

    while (nextHorzTouchX >= 0 && nextHorzTouchX <= data->width_window &&
           nextHorzTouchY >= 0 && nextHorzTouchY <= data->height_window)
    {
        xToCheck = nextHorzTouchX;
        yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0); // Ajustement pour les rayons se dirigeant vers le haut

        if (!check_intersection_mini(data, xToCheck, yToCheck))
            break;
        else 
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    return distanceBetweenPoints(player_x, player_y, nextHorzTouchX, nextHorzTouchY);
}

double check_vertical_mini(t_config *data, double rayAngle)
{
    int isRayFacingDown;
    int isRayFacingUp;
    int isRayFacingRight;
    int isRayFacingLeft;
    double Vintercept;
    double yintercept;
    double xstep;
    int player_x;
    int player_y;
    double ystep;
    double nextVertTouchX;
    double nextVertTouchY;
    double xToCheck;
    double yToCheck;

    rayAngle = normalizeAngle(rayAngle);
    player_x = data->player.x_mini + data->move_x_min;
    player_y = data->player.y_mini + data->move_y_min;

    isRayFacingDown = (rayAngle > 0 && rayAngle < M_PI);
    isRayFacingUp = !isRayFacingDown;
    isRayFacingRight = (rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI);
    isRayFacingLeft = !isRayFacingRight;

    // Calcul des intercepts verticaux
    Vintercept = floor(player_x / size_) * size_;
    if (isRayFacingRight)
        Vintercept += size_;
    yintercept = player_y + (Vintercept - player_x) * tan(rayAngle);

    xstep = size_;
    if (isRayFacingLeft)
        xstep *= -1;

    ystep = size_ * tan(rayAngle);
    if (isRayFacingUp && ystep > 0)
        ystep *= -1;
    if (isRayFacingDown && ystep < 0)
        ystep *= -1;

    nextVertTouchX = Vintercept;
    nextVertTouchY = yintercept;

    while (nextVertTouchX >= 0 && nextVertTouchX <= data->width_window &&
           nextVertTouchY >= 0 && nextVertTouchY <= data->height_window)
    {
        xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0); // Ajustement pour les rayons se dirigeant vers la gauche
        yToCheck = nextVertTouchY;

        if (!check_intersection_mini(data, xToCheck, yToCheck))
            break;
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    return distanceBetweenPoints(player_x, player_y, nextVertTouchX, nextVertTouchY);
}