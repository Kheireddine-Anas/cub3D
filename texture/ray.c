/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:33:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/31 12:30:12 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double normalizeAngle(double angle)
{
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0) 
        angle = (2 * M_PI) + angle; 
    if (angle > 2 * M_PI)
        angle = angle - (2 * M_PI);
    return angle;
}

double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}


void    castAllRays(t_config **data)
{
    double ray_x;
    double ray_y;
    double dis_vertical;
    double dis_horizontal;
    int  ray = 0;
    double dis;
    int		player_x = (*data)->player.x +(*data)->move_x;
   	int		player_y = (*data)->player.y +(*data)->move_y;
  (*data)->ray.ray_ngl = ((*data)->player.angle +(*data)->mouv_camera_left) - ((*data)->player.fov_rd / 2);;

    while (ray < (*data)->width_window)
    {
        dis_horizontal= check_horizontal(data,(*data)->ray.ray_ngl);
        dis_vertical = check_vertical(data,(*data)->ray.ray_ngl);
        (*data)->ray.flag = 0;
        if (dis_horizontal < dis_vertical)
        {
           (*data)->ray.flag = 1;
            dis = dis_horizontal;
        }
        else
            dis = dis_vertical;
        ray_x = player_x +   dis  * cos((*data)->ray.ray_ngl);
        ray_y = player_y +  dis  * sin((*data)->ray.ray_ngl);
       render_wall(data, ray, dis,(*data)->ray.ray_ngl);
       (*data)->ray.ray_ngl += ((*data)->player.fov_rd /(*data)->width_window); 
        ray++;
    }
}

void    castAllRays_minimap(t_config *data)
{
    double ray_x;
    double ray_y;
    double dis_vertical;
    double dis_horizontal;
    int  ray = 0;
    double dis;
    double ray_angle;
    int		player_x = data->player.x_mini + data->move_x_min;
   	int		player_y = data->player.y_mini + data->move_y_min;
    ray_angle = (data->player.angle + data->mouv_camera_left) - (data->player.fov_rd / 2);;
    while (ray < data->width_window)
    {
        dis_horizontal = check_horizontal_mini(data,ray_angle);
        dis_vertical =  check_vertical_mini(data,ray_angle);
        if (dis_horizontal < dis_vertical)
            dis = dis_horizontal;
        else
            dis = dis_vertical;
        ray_x = player_x +   dis  * cos(ray_angle);
        ray_y = player_y +  dis  * sin(ray_angle);
        draw_line(data, player_x, player_y,  ray_x , ray_y, ORNG );
       ray_angle += (data->player.fov_rd / data->width_window); 
        ray++; 
    }
}
