#include "cub3d.h"

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
