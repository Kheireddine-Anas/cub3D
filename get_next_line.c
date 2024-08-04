/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:00:14 by akheired          #+#    #+#             */
/*   Updated: 2024/08/03 16:03:30 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_str(int fd, char *str)
{
	char	*buff;
	int		readed;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	readed = 1;
	while (!find_new_line(str) && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
		{
			free(str);
			free(buff);
			return (NULL);
		}
		buff[readed] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	holder = read_str(fd, holder);
	if (!holder)
		return (NULL);
	line = ft_first_line(holder);
	holder = ft_last_line(holder);
	return (line);
}
