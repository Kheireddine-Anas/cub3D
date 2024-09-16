/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:22:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/15 10:25:00 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_square(t_config **data, int x, int y, int color)
{
    int i, j;
    int x_map, y_map;
    i = 0;

    while (i < size_)
    {
        j = 0;
        while (j < size_)
        {
            x_map = x + j;
            y_map = y + i;
            if (x_map >= 0 && x_map < (*data)->width_window &&
            y_map >= 0 && y_map <= (*data)->height_window)
                mlx_put_pixel((*data)->img, x_map, y_map, color);
            j++;
        }
        i++;
    }
}
void draw_square_player(t_config **data, int x, int y, int color)
{
    int i, j;
    int x_map, y_map;
    i = 0;

    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            x_map = x + j;
            y_map = y + i;
            if (x_map >= 0 && x_map < (*data)->width_window &&
            y_map >= 0 && y_map <= (*data)->height_window)
                mlx_put_pixel((*data)->img, x_map, y_map, color);
            j++;
        }
        i++;
    }
}
void draw_card(t_config *data)
{
    int i, j;
    i = 0;

    while (i < 208)
    {
        j = 0;
        while (j < 208)
        {
            mlx_put_pixel(data->img, j, i, GREY);
            j++;
        }
        i++;
    }
}


void	free_doube_eraay(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
