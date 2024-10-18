/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 08:48:04 by akheired          #+#    #+#             */
/*   Updated: 2024/08/15 18:29:50 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*init_color(char **line)
{
	int	*colors;
	int	nb;
	int	i;
	int	j;

	colors = (int *)malloc(sizeof(int) * 3);
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

char	*ft_substr(char *s, int start, int len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start > len)
		str = (char *)malloc(len + 1);
	else
		str = (char *)malloc(ft_strlen(s) - start + 1);
	if (!str)
		return (NULL);
	while (len-- > 0 && s[start])
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*dst;
	int		i;

	i = -1;
	dst = (char *)malloc(ft_strlen(s) + 1);
	if (!dst)
		return (NULL);
	while (s[++i])
		dst[i] = s[i];
	dst[i] = '\0';
	return (dst);
}

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
