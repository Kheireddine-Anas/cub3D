/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:48:04 by akheired          #+#    #+#             */
/*   Updated: 2024/10/18 13:09:22 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*init_color(char **line)
{
	int	*colors;
	int	nb;
	int	i;
	int	j;

	colors = ft_calloc(3, sizeof(int));
	if (!colors)
		return (NULL);
	i = 0;
	while (line[i] && i < 3)
	{
		nb = 0;
		j = 0;
		while (line[i][j] == ' ' || line[i][j] == '\t')
			j++;
		while (line[i][j] >= '0' && line[i][j] <= '9')
		{
			nb = nb * 10 + (line[i][j] - '0');
			j++;
		}
		colors[i] = nb;
		i++;
	}
	return (colors);
}
