/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 21:22:04 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/30 16:42:27 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_square(t_config **data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size_)
	{
		j = 0;
		while (j < size_)
		{
			mlx_put_pixel((*data)->img, x + j, y + i, color);
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
