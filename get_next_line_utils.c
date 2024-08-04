/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:04:38 by akheired          #+#    #+#             */
/*   Updated: 2024/08/03 16:03:37 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	find_new_line(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strjoin(char *holder, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!holder)
	{
		holder = malloc(sizeof(char));
		holder[0] = '\0';
	}
	i = -1;
	j = 0;
	if (!holder || !buff)
		return (NULL);
	str = malloc(ft_strlen(holder) + ft_strlen(buff) + 1);
	if (str == NULL)
		return (NULL);
	while (holder[++i])
		str[i] = holder[i];
	while (buff[j])
		str[i++] = buff[j++];
	str[i] = '\0';
	free(holder);
	return (str);
}

char	*ft_first_line(char *first_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!first_str[i])
		return (NULL);
	while (first_str[i] && first_str[i] != '\n')
		i++;
	if (first_str[i] == '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (first_str[++i] && first_str[i] != '\n')
		str[i] = first_str[i];
	if (first_str[i] == '\n')
	{
		str[i] = first_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_last_line(char *last_str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (last_str[i] && last_str[i] != '\n')
		i++;
	if (!last_str[i])
	{
		free(last_str);
		return (NULL);
	}
	if (last_str[i] == '\n')
		i++;
	new_str = malloc((ft_strlen(last_str) - i) + 1);
	if (!new_str)
		return (NULL);
	while (last_str[i])
		new_str[j++] = last_str[i++];
	new_str[j] = '\0';
	free(last_str);
	return (new_str);
}
