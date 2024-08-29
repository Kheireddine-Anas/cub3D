/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:33:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/29 13:24:28 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double normalizeAngle(double angle)
{
    angle = remainder(angle, TWO_PI);
    if (angle < 0) 
        angle += TWO_PI;
    return angle;
}
int mapHasWallAt(t_config *data,float x, float y)
{
    if (x < 0 || x >= data->width_window || y < 0 || y >= data->height_window) {
        return TRUE;
    }
    int mapGridIndexX = floor(x / data->size);
    int mapGridIndexY = floor(y / data->size);
	if (mapGridIndexX < 0 || mapGridIndexX >= data->map->map_width || mapGridIndexY < 0 || mapGridIndexY >= data->map->map_height) {
		return TRUE;
	}
    return data->map->map_buffer[mapGridIndexY][mapGridIndexX] != 0;
}

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


void    castAllRays(t_config *data)
{
    double ray_x;
    double ray_y;
    double end_angle;
    double dis_vertical;
    double dis_horizontal;
    double ray_angle;
    double dis;
    int		player_x = data->player.x + data->move_x;
   	int		player_y = data->player.y + data->move_y;
    ray_angle = (data->player.angle + data->mouv_camera_left) - FOV / 2;
    end_angle = (data->player.angle + data->mouv_camera_left) + FOV / 2;

    while (ray_angle <= end_angle)
    {
        dis_horizontal= chek_orizental(data,  ray_angle);
        dis_vertical = chek_vertical(data,  ray_angle);
        if (dis_horizontal < dis_vertical)
            dis = dis_horizontal;
        else
            dis = dis_vertical;
        ray_x = player_x +  dis * cos(ray_angle);
        ray_y = player_y + dis * sin(ray_angle);
        draw_line(data, player_x, player_y,  ray_x , ray_y, 0xFF9300FF);
        ray_angle += RAY_STEP;
    }
}
