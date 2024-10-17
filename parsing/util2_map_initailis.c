/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2_map_initailis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:42:38 by ahamdi            #+#    #+#             */
/*   Updated: 2024/10/17 10:56:04 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	get_height_map(t_config **data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open_map(data);
	while (1)
	{
		line = get_next_line(fd);
		if ((!ft_strchr(line, ',') && (ft_strchr(line, '1') || ft_strchr(line,
						'0'))) || !line)
			break ;
		free(line);
	}
	while (1)
	{
		if (!line)
			break ;
		else if (!ft_strchr(line, '1') && !ft_strchr(line, '0'))
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	(*data)->map->map_height = i;
}

char	*map_info(t_config **data)
{
	char	*line;
	char	**splite;
	int		i;
	char	*tmp;

	i = 0;
	(*data)->map->fd = open_map(data);
	while (1)
	{
		line = get_next_line((*data)->map->fd);
		if (!line)
			break ;
		if ((!ft_strchr(line, ',') && (ft_strchr(line, '1') || ft_strchr(line,
						'0'))))
			break ;
		if (ft_strchr(line, '\n'))
			line = delet_newlin(line);
		splite = ft_split(line, ' ');
		if (splite[0] && ft_strcmp(splite[0], "NO") == 0)
			(*data)->map->north_texture = ft_strdup(splite[1]);
		else if (splite[0] && ft_strcmp(splite[0], "SO") == 0)
			(*data)->map->south_texture = ft_strdup(splite[1]);
		else if (splite[0] && ft_strcmp(splite[0], "WE") == 0)
			(*data)->map->west_texture = ft_strdup(splite[1]);
		else if (splite[0] && ft_strcmp(splite[0], "EA") == 0)
			(*data)->map->east_texture = ft_strdup(splite[1]);
		else if (splite[0] && ft_strcmp(splite[0], "F") == 0)
		{
			if (!splite[2])
				(*data)->map->floor_color = ft_strdup(splite[1]);
			else
			{
				i = 1;
				while (splite[i])
				{
					tmp = (*data)->map->floor_color;
					(*data)->map->floor_color = ft_strjoin((*data)->map->floor_color,
							splite[i]);
					free(tmp);
					i++;
				}
			}
		}
		else if (splite[0] && ft_strcmp(splite[0], "C") == 0)
		{
			if (!splite[2])
				(*data)->map->ceiling_color = ft_strdup(splite[1]);
			else
			{
				i = 1;
				while (splite[i])
				{
					tmp = (*data)->map->ceiling_color;
					(*data)->map->ceiling_color = ft_strjoin((*data)->map->ceiling_color,
							splite[i]);
					free(tmp);
					i++;
				}
			}
		}
		else if (ft_strlen(line) != 2 && (line[0] != '\n' && line[1] != '\0'))
		{
			ft_putstr_fd("cd", 2);
			ft_putstr_fd("invalid map", 2);
			exit(1);
		}
		free_double_array(splite);
		free(line);
	}
	return (line);
}
int	openfil(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

void	chekeinfo(t_config **data)
{
	if (!(*data)->map->west_texture || !(*data)->map->north_texture
		|| !(*data)->map->south_texture || !(*data)->map->east_texture
		|| !(*data)->map->ceiling_color || !(*data)->map->floor_color)
	{
		ft_putstr_fd("invalid map", 2);
		exit(1);
	}
	if (openfil((*data)->map->west_texture) == -1
		|| openfil((*data)->map->north_texture) == -1
		|| openfil((*data)->map->south_texture) == -1
		|| openfil((*data)->map->east_texture) == -1)
	{
		ft_putstr_fd("invalid map", 2);
		exit(1);
	}
}

void	map_inistialisation(t_config **data)
{
	int		i;
	char	*line;

	i = 0;
	get_height_map(data);
	(*data)->map->map_buffer = ft_calloc((*data)->map->map_height + 1,
			sizeof(char *));
	line = map_info(data);
	chekeinfo(data);
	(*data)->map->map_width = ft_strlen(line);
	(*data)->map->map_width *= SIZE_;
	while (1)
	{
		if (!line)
			break ;
		else if (!ft_strchr(line, '1') && !ft_strchr(line, '0'))
		{
			free(line);
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
		if (ft_strchr(line, '\n'))
			line = delet_newlin(line);
		(*data)->map->map_buffer[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line((*data)->map->fd);
	}
	(*data)->map->map_buffer[i] = NULL;
	free(line);
	close((*data)->map->fd);
}
