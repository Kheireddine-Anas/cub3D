#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void	*ft_calloc(int count, int size)
{
	char	*memory;
	int		i;

	i = 0;
	memory = malloc(count * size);
	if (memory == NULL)
		return (0);
	while (i < count * size)
	{
		memory[i] = 0;
		i++;
	}
	return (memory);
}
int ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s &&s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned char	*sbs;
	size_t			i;

	if (len > ft_strlen(s) - start)
		sbs = malloc(ft_strlen(s) - start + 1);
	else
		sbs = malloc(len + 1);
	if (!sbs)
		return (0);
	i = 0;
	while (s[start] && len)
	{
		sbs[i] = s[start];
		start++;
		i++;
		len--;
	}
	sbs[i] = '\0';
	return ((char *)sbs);
}

int	word(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '\n' && (s[i] == ' ' || s[i] == '\t'))
			i++;
		if (s[i] && s[i] != '\n')
			count++;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	return (count);
}

int	len_word(const char *s, int i)
{
	int	len_s;

	len_s = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
	{
		i++;
		len_s++;
	}
	return (len_s);
}

char	**my_split(char const *s)
{
	char	**tab;
	int		len_s;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (0);
	tab = ft_calloc(word(s) + 1, sizeof(char *));
	if (!tab)
		return (0);
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		len_s = len_word(s, i);
		if (++j < word(s))
			tab[j] = ft_substr(s, i, len_s);
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
	}
	return (tab);
}


int main()
{
    const char *str = "	C  225 	, 	30	,	0 ";
    char **result = my_split(str);

    if (!result)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Split strings:\n");
    for (int i = 0; result[i] != NULL; i++)
    {
        printf("%s\n", result[i]);
        free(result[i]); // Free each string allocated
    }

    free(result); // Free the array of strings

    return 0;
}