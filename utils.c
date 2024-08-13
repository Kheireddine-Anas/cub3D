/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:48:04 by akheired          #+#    #+#             */
/*   Updated: 2024/08/12 11:48:15 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (-1);
	while (s1[i] || s2[i])
	{
		if ((s1[i] != s2[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*hld;
	size_t	i;

	i = -1;
	hld = malloc(count * size);
	if (!hld)
		return (NULL);
	while (++i < size)
		hld[i] = 0;
	return (hld);
}
