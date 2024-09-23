/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:38:31 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/23 15:09:46 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void while_loop(t_config **data, int i, int j, int player_x)
{
    int x;
    int y;
    int player_y;

    player_y = (*data)->player.y + (*data)->move_y;
    y = i * size_;
    if (y > (player_y - 100) && y < (player_y + 100))
	{
			x = j * size_;
			if ((x > (player_x - 100) && x < (player_x + 100)))
			{
				if ((*data)->map->map_buffer[i][j] == '1')
            		draw_square(data, x - (player_x - 100), y - (player_y - 100), WHI);
				else if ((*data)->map->map_buffer[i][j] == 'P')
					draw_square(data, x - (player_x - 100), y - (player_y - 100), BLU);
        		else if ((*data)->map->map_buffer[i][j] == 'K')
				{
					(*data)->sprid_x = x;
					(*data)->strat_y = y;
					draw_square(data, x - (player_x - 100), y - (player_y - 100), RED);
				}	
				else
					draw_square(data, x - (player_x - 100), y - (player_y - 100), GREY);
			}
	}
}

void draw_minimap(t_config **data)
{
	int i = 0;
	int j;
	int	y;
	int player_x;
	int player_y;

	draw_card(*data);
	player_x = (*data)->player.x + (*data)->move_x;
	player_y = (*data)->player.y + (*data)->move_y;
	while ((*data)->map->map_buffer[i])
	{ 
		j = 0;
		y = i * size_;
		while ((*data)->map->map_buffer[i][j])
    	{
           while_loop(data, i, j, player_x);
            j++;
        }
		i++;
	}
	draw_square_player(data, ((*data)->player.x / 2) - (((*data)->player.x / 2) - 100), ((*data)->player.y / 2) - (((*data)->player.y / 2) - 100), ORNG);
}

void draw_centered_image(t_config *data, mlx_texture_t *texture)
{
    uint32_t     x;
    uint32_t     y;
    uint32_t *arr;
    int start_x;
    int start_y;

    start_x = ( data->width_window - texture->width) / 2;
    start_y = data->height_window- texture->height;
    arr = (uint32_t *)texture->pixels;
    y = 0; 
    while(y < texture->height)
    {
        x = 0;
        while( x < texture->width)
        {
            int texture_x = x;
            int texture_y = y;
            uint32_t color = arr[texture_y * texture->width + texture_x];
            if ((color & 0xFF000000) != 0)
			{
                mlx_put_pixel(data->img, start_x + x, start_y + y, reverse_bytes(color));
            }
            x++;
        }
        y++;
    }
}

void draw_enter(t_config *data, mlx_texture_t *texture)
{
    uint32_t x;
    uint32_t y;
    uint32_t color;
    uint32_t *arr;
    int start_x;
    int start_y;

    start_x = (data->width_window - texture->width) / 2;
    start_y = (data->height_window- texture->height) / 2; // Centré verticalement
    arr = (uint32_t *)texture->pixels;
    y = 0;
    while( y < texture->height)
    {
        x = 0;
        while( x < texture->width)
        {
            color = arr[y * texture->width + x];
            if ((color & 0xFF000000) != 0)
			{
                mlx_put_pixel(data->img, start_x + x, start_y + y, reverse_bytes(color));
            }
            x++;
        }
        y++;
    }
}

int	close_window(t_config **data)
{
	if ((*data)->mlx_ptr && (*data)->img)
	{
		mlx_close_window((*data)->mlx_ptr);
	}
	ft_putstr_fd(" close window\n", 1);
	destroy_data(data);
	exit(0);
}
