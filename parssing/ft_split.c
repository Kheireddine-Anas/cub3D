/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:34:14 by akheired          #+#    #+#             */
/*   Updated: 2024/08/06 11:50:49 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	count_word(const char *str)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\n' && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] && str[i] != '\n')
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
	while (str[i] && str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

static char	*str_alloc(const char *str)
{
	char	*word;
	size_t	i;
	size_t	worldlen;

	i = -1;
	worldlen = count_len(str);
	word = (char *)malloc(sizeof(char) * (worldlen + 1));
	if (!word)
		return (NULL);
	while (++i < worldlen)
		word[i] = str[i];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *str)
{
	char	**strings;
	size_t	i;

	i = 0;
	strings = (char **)malloc(sizeof(char *) * (count_word(str) + 1));
	if (!strings)
		return (NULL);
	while (*str != '\0')
	{
		while (*str && (*str == ' ' || str[i] == '\t'))
			str++;
		if (*str)
		{
			strings[i] = str_alloc(str);
			if (!strings[i])
				return (NULL);
			i++;
		}
		while (*str && str[i] != ' ' && str[i] != '\t')
			str++;
	}
	strings[i] = 0;
	return (strings);
}
