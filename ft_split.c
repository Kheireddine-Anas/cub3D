/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:34:14 by akheired          #+#    #+#             */
/*   Updated: 2024/08/16 08:16:00 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	cwords(char const *str, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (*(str + i))
	{
		if (*(str + i) != c)
		{
			counter++;
			while (*(str + i) && *(str + i) != c)
				i++;
		}
		else if (*(str + i) == c)
			i++;
	}
	return (counter);
}

static size_t	word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*(s + i) && *(s + i) != c)
		i++;
	return (i);
}

static void	fr_er(char **dst, size_t i)
{
	while (i > 0)
	{
		i--;
		free(*(dst + i));
	}
	free (dst);
}

static char	**spliters(char *s, char c, char **dst, size_t words)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(dst + i) = ft_substr(s, j, word_len((s + j), c));
		if (!*(dst + i))
		{
			fr_er(dst, i);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(dst + i) = NULL;
	return (dst);
}

char	**ft_split(char *s, char c)
{
	size_t	words;
	char	**dst;

	if (!s)
		return (NULL);
	words = cwords(s, c);
	dst = malloc(sizeof(char *) * (words + 1));
	if (!dst)
		return (NULL);
	dst = spliters(s, c, dst, words);
	return (dst);
}
