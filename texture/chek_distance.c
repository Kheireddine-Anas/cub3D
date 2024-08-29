/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:37:07 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/29 13:46:31 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int chek_intersection(t_config *data, double xintercept, double Hintercept)
{
   if (xintercept < 0 || xintercept >= data->width_window || Hintercept < 0 ||Hintercept >= data->height_window)
        return 0;
    int mapGridIndexX = floor(xintercept / data->size);
    int mapGridIndexY = floor(Hintercept / data->size);
    if (mapGridIndexX < 0 || mapGridIndexX >= data->map->map_width || mapGridIndexY < 0 || mapGridIndexY >= data->map->map_height)
        return 0;
    if (data->map->map_buffer[mapGridIndexY][mapGridIndexX] == '1')
        return 0;
    return 1;
}

double chek_orizental(t_config *data, double rayAngle)
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

    rayAngle = normalizeAngle(rayAngle);;
    player_x = data->player.x + data->move_x;
    player_y = data->player.y + data->move_y;
    if (rayAngle > 0 && rayAngle < PI)
        isRayFacingDown = 1;
    else
        isRayFacingDown = 0;
    isRayFacingUp = !isRayFacingDown;

    if (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI)
        isRayFacingRight = 1;
    else
        isRayFacingRight = 0;
    isRayFacingLeft = !isRayFacingRight;
    Hintercept = floor(player_y / data->size) * data->size;
    Hintercept += isRayFacingDown ? data->size: 0;
    xintercept = player_x + (Hintercept - player_y) / tan(rayAngle);

    ystep = data->size;
    if (isRayFacingUp)
        ystep *= -1;
    xstep = data->size / tan(rayAngle);
    if (isRayFacingLeft && xstep > 0)
        xstep *= -1;
    if (isRayFacingRight && xstep < 0)
        xstep *= -1;
    while (chek_intersection(data, xintercept, Hintercept))
    {
        xintercept += xstep;
        Hintercept += ystep;
    }
    return (distanceBetweenPoints(player_x, player_y, xintercept,  Hintercept));
}

double chek_vertical(t_config *data, double rayAngle)
{
    int isRayFacingDown;
    int isRayFacingUp;
    int isRayFacingRight;
    int isRayFacingLeft;
    double xintercept;
    double Vintercept;
    double xstep;
    int player_x;
    int player_y;
    double ystep;

    rayAngle = normalizeAngle(rayAngle);;
    player_x = data->player.x + data->move_x;
    player_y = data->player.y + data->move_y;
    if (rayAngle > 0 && rayAngle < PI)
        isRayFacingDown = 1;
    else
        isRayFacingDown = 0;
    isRayFacingUp = !isRayFacingDown;

    if (rayAngle < 0.5 * PI || rayAngle > 1.5 * PI)
        isRayFacingRight = 1;
    else
        isRayFacingRight = 0;
    isRayFacingLeft = !isRayFacingRight;
    Vintercept = floor(player_x / data->size) * data->size;
    if (isRayFacingRight)
        Vintercept += data->size ;
    xintercept = player_x + (Vintercept - player_y) / tan(rayAngle);
    xstep = data->size;
    if (isRayFacingLeft)
        xstep *= -1;
    ystep = data->size * tan(rayAngle);
    if (isRayFacingUp && ystep > 0)
    ystep *= -1;
    if(isRayFacingDown && ystep < 0)
        ystep *= -1;
    if (isRayFacingLeft && xstep > 0)
        xstep *= -1;
    while (chek_intersection(data, xintercept, Vintercept))
    {
        xintercept += xstep;
        Vintercept += ystep;
    }
    return (distanceBetweenPoints(player_x, player_y, xintercept,  Vintercept));
   
}
