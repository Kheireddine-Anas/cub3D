/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kebord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:49:12 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/30 19:47:19 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player(t_config **data, int i)
{
	if (i == 1)
	{
		(*data)->mouv_camera_left += ROTATION_SPEED;
		if ((*data)->player.angle + (*data)->mouv_camera_left > 2 * M_PI)
			(*data)->mouv_camera_left -= 2 * M_PI;
	}
	else
	{
		(*data)->mouv_camera_left -= ROTATION_SPEED;
		if ((*data)->player.angle + (*data)->mouv_camera_left < 0)
			(*data)->mouv_camera_left += 2 * M_PI;
	}
}

void	move_player(t_config **data)
{
	double map_grid_y;
	double map_grid_x;
	double new_x;
	double new_y;
	static  double	move_x = 0;
	static double	move_y = 0;
	static  double	move_x_min = 0;
	static double	move_y_min = 0;

	new_x = (*data)->player.x + (*data)->move_x;                                                                                                                                                                     
	new_y = (*data)->player.y + (*data)->move_y	;                                                                                                                                                                     
    map_grid_x = new_x / (*data)->size; 
	map_grid_y =  new_y / (*data)->size;                                                                                                                                                                
	if (((*data)->map->map_buffer[(int)(new_y - move_y)  / (*data)->size][(int)map_grid_x] != '1' 
		&& (*data)->map->map_buffer[(int)map_grid_y][(int)(new_x - move_x)/  (*data)->size] != '1' ) ||
		(*data)->map->map_buffer[(int)map_grid_y][(int)map_grid_x] != '1')
	{
		move_x = (*data)->move_x;
		move_y = (*data)->move_y;
		move_x_min = (*data)->move_x_min;
		move_y_min = (*data)->move_y_min;
		mlx_delete_image ((*data)->mlx_ptr, (*data)->img);
		draw_mini_map(data);
	}
	else
	{
		(*data)->move_x = move_x;
		(*data)->move_y = move_y;
		(*data)->move_x_min = move_x_min;
		(*data)->move_y_min = move_y_min;
	}
}

void	hook(mlx_key_data_t keydata, void *ml) // hook the player
{
	t_config	**data;
	double old_y;
	double old_x;
	double new_x;
	double new_y;
	data = ml;
	if (keydata.key == 256) // exit the game
		close_window(data);
	if (keydata.key == MLX_KEY_RIGHT) // rotate right
		rotate_player(data, 1);
	if (keydata.key == MLX_KEY_LEFT) // rotate left
		rotate_player(data, 0);
	old_x = ((*data)->player.x + (*data)->move_x)  / (*data)->size;
	old_y = ((*data)->player.y + (*data)->move_y)  / (*data)->size;
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
	{
		new_x = ((*data)->player.x + (*data)->move_x + cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED)  / (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y + sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y]&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)new_y] && (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x += cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y += sin((*data)->player.angle +(*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_x_min += cos((*data)->player.angle + (*data)->mouv_camera_left) *PLAYER_SPEED_MINI_MAP;
			(*data)->move_y_min += sin((*data)->player.angle +(*data)->mouv_camera_left) *PLAYER_SPEED_MINI_MAP;
		}
	}
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) // move down
	{
		new_x = ((*data)->player.x + (*data)->move_x - cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y - sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y] && (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)new_y] && (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x -= cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y -= sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_x_min -= cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED_MINI_MAP;
			(*data)->move_y_min -= sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED_MINI_MAP;
		}
	}
	if (keydata.key == MLX_KEY_A)
	{
		new_x = ((*data)->player.x + (*data)->move_x + sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED)  / (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y - cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y]&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)new_y] && (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x += sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y -= cos((*data)->player.angle +(*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_x_min += sin((*data)->player.angle + (*data)->mouv_camera_left) *PLAYER_SPEED_MINI_MAP;
			(*data)->move_y_min -= cos((*data)->player.angle +(*data)->mouv_camera_left) *PLAYER_SPEED_MINI_MAP;
		}
	}
	if (keydata.key == MLX_KEY_D) // move down
	{
		new_x = ((*data)->player.x + (*data)->move_x - sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y + cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED) / (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y] && (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)new_y] && (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x -= sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y += cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_x_min -= sin((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED_MINI_MAP;
			(*data)->move_y_min += cos((*data)->player.angle + (*data)->mouv_camera_left) * PLAYER_SPEED_MINI_MAP;
		}
	}
	move_player(data);
}



void	fontion_mlx_and_draw(t_config **data)
{
	draw_mini_map(data);
	mlx_key_hook((*data)->mlx_ptr, hook, data);
}
