/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_distance_vertical.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:37:07 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/25 16:25:18 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void initialize_variables_vertical(t_config **data)
{
    (*data)->ray.ray_ngl = normalizeAngle((*data)->ray.ray_ngl);
    (*data)->chek_vertical.isRayFacingDown = ((*data)->ray.ray_ngl > 0 && (*data)->ray.ray_ngl < M_PI);
    (*data)->chek_vertical.isRayFacingUp = !(*data)->chek_vertical.isRayFacingDown;
   (*data)->chek_vertical.isRayFacingRight = ((*data)->ray.ray_ngl < 0.5 * M_PI || (*data)->ray.ray_ngl > 1.5 * M_PI);
    (*data)->chek_vertical.isRayFacingLeft = !(*data)->chek_vertical.isRayFacingRight;
}

void calculate_intercepts_and_steps_vertical(t_config **data)
{
    double player_x;
    double player_y;

    player_x = (*data)->player.x + (*data)->move_x;
    player_y = (*data)->player.y + (*data)->move_y;
    (*data)->chek_vertical.Vintercept = floor(player_x / (*data)->size) * (*data)->size;
    if ((*data)->chek_vertical.isRayFacingRight)
        (*data)->chek_vertical.Vintercept += (*data)->size;
    (*data)->chek_vertical.yintercept = player_y + ((*data)->chek_vertical.Vintercept - player_x) * tan((*data)->ray.ray_ngl);
    (*data)->chek_vertical.xstep = (*data)->size;
    if ((*data)->chek_vertical.isRayFacingLeft)
        (*data)->chek_vertical.xstep *= -1;
   (*data)->chek_vertical.ystep= (*data)->size * tan((*data)->ray.ray_ngl);
    if ((*data)->chek_vertical.isRayFacingUp && (*data)->chek_vertical.ystep > 0)
        (*data)->chek_vertical.ystep *= -1;
    if ((*data)->chek_vertical.isRayFacingDown && (*data)->chek_vertical.ystep < 0)
        (*data)->chek_vertical.ystep *= -1;
}

double check_vertical(t_config **data, int i)
{
    initialize_variables_vertical(data);
    calculate_intercepts_and_steps_vertical(data);
    while ((*data)->chek_vertical.Vintercept >= 0 && (*data)->chek_vertical.Vintercept <= ((*data)->map->map_width * size_)&&
           (*data)->chek_vertical.yintercept >= 0 && (*data)->chek_vertical.yintercept  <= ((*data)->map->map_height * size_) )
    {
        if ((*data)->chek_vertical.isRayFacingLeft)
            (*data)->chek_vertical.xToCheck = (*data)->chek_vertical.Vintercept - 1;
        else
            (*data)->chek_vertical.xToCheck = (*data)->chek_vertical.Vintercept;
        (*data)->chek_vertical.yToCheck = (*data)->chek_vertical.yintercept;

        if (!check_intersection(*data, (*data)->chek_vertical.xToCheck, (*data)->chek_vertical.yToCheck))
            break;
        else
        {
            (*data)->chek_vertical.Vintercept += (*data)->chek_vertical.xstep;
            (*data)->chek_vertical.yintercept += (*data)->chek_vertical.ystep;
        }
    }
    (*data)->ray.vert_x = (*data)->chek_vertical.xToCheck;
    (*data)->ray.vert_y = (*data)->chek_vertical.yToCheck;
     (*data)->rays[i].vert_x = (*data)->chek_vertical.xToCheck;
    (*data)->rays[i].vert_y = (*data)->chek_vertical.yToCheck;
    return (distanceBetweenPoints((*data)->player.x + (*data)->move_x, (*data)->player.y + (*data)->move_y, (*data)->chek_vertical.Vintercept, (*data)->chek_vertical.yintercept));
}
