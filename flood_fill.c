#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

void flood_fill(t_config *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->map_size || y >= len(map->cp_map[x]) || 
		map->cp_map[x][y] == '1' || map->cp_map[x][y] == ' ' || map->cp_map[x][y] == 'V')
		return ;
	map->cp_map[x][y] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void valid_paths(t_config *map)
{
	int i;
	int j;
	// Apply flood fill from player's position
	flood_fill(map, map->player_x, map->player_y);
	i = -1;
	while (map->cp_map[++i]) //Print The Map after Flood Fill
	{
		j = -1;
		while (map->cp_map[i][++j] != '\n' && map->cp_map[i][j] != '\0')
		{
			printf("%c", map->cp_map[i][j]);
		}
		printf("\n");
	}
	i = -1;
	while (map->cp_map[++i])
	{
		j = -1;
		while (map->cp_map[i][++j] != '\n' && map->cp_map[i][j] != '\0')
		{
			if (map->cp_map[i][j] == 'COINS')
			{
				ft_error("Error\nUnreachable Coin!\n");
				return;
			}
		}
	}
	printf("The map is valid!\n");
}
