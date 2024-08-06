/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akheired <akheired@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 16:29:18 by akheired          #+#    #+#             */
/*   Updated: 2024/08/05 19:46:27 by akheired         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	count_word(const char *str)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			count++;
		while (str[i] && str[i] != ' ' && str[i] != '\t')
			i++;
	}
	return (count);
}

static size_t	count_len(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		i++;
	return (i);
}

static char	*str_alloc(const char *str)
{
	char	*word;
	int		i;
	int		worldlen;

	i = 0;
	worldlen = count_len(str);
	word = (char *)malloc(sizeof(char) * (worldlen + 1));
	if (!word)
		return (NULL);
	while (i < worldlen)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**spliter(char const *str)
{
	char	**strings;
	size_t	i;

	i = 0;
	strings = (char **)malloc(sizeof(char *) * (count_word(str) + 1));
	if (!strings)
		return (NULL);
	while (*str != '\0')
	{
		while (*str && (*str == ' ' || *str == '\t'))
			str++;
		if (*str)
		{
			strings[i] = str_alloc(str);
			if (!strings[i])
				return (NULL);
			i++;
		}
		while (*str && *str != ' ' && *str != '\t')
			str++;
	}
	strings[i] = NULL;
	return (strings);
}
