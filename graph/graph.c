#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MLX42/include/MLX42/MLX42.h"

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
}	t_game;

void	close_win()
{
	exit(1);
}

void	my_hook(mlx_key_data_t keys, void *param)
{
	
	if (keys.action == MLX_PRESS) //SHOE KEY NUMER
		printf("%d >> %d\n", keys.os_key, keys.key);
	if (keys.key == MLX_KEY_L && (keys.action == MLX_REPEAT && keys.action == MLX_PRESS))
		puts("!");
	// if (keys.key == MLX_KEY_J && keys.action == MLX_PRESS)
	// 	printf("%d | %d\n", keys.os_key, keys.key);
	if (keys.key == MLX_KEY_ESCAPE && keys.action == MLX_PRESS)
		exit(0);
	(void)param;
}

void	show_game(t_game *game)
{
	game->mlx = mlx_init(1200, 1000, "cub3D", false);
	mlx_image_t* img = mlx_new_image(game->mlx, 500, 128);

	// Set the channels of each pixel in our image to the maximum byte value of 255. 
	memset(img->pixels, 1501, 500);

	// Draw the image at coordinate (0, 0).
	mlx_image_to_window(game->mlx, img, 50, 500);
	mlx_key_hook(game->mlx, &my_hook, NULL);
	mlx_loop(game->mlx);
}

int	main()
{
	t_game	game;

	show_game(&game);
}