/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kebord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:49:12 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/15 12:46:31 by ahamdi           ###   ########.fr       */
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
	double			map_grid_y;
	double			map_grid_x;
	double			new_x;
	double			new_y;
	static double	move_x = 0;
	static double	move_y = 0;

	new_x = (*data)->player.x + (*data)->move_x;
	new_y = (*data)->player.y + (*data)->move_y;
	map_grid_x = new_x / (*data)->size;
	map_grid_y = new_y / (*data)->size;
	if (((*data)->map->map_buffer[(int)((new_y - move_y) / (*data)->size)][(int)map_grid_x] != '1' && 
     (*data)->map->map_buffer[(int)((new_y - move_y) / (*data)->size)][(int)map_grid_x] != 'P' &&
     (*data)->map->map_buffer[(int)map_grid_y][(int)((new_x - move_x) / (*data)->size)] != '1' && 
     (*data)->map->map_buffer[(int)map_grid_y][(int)((new_x - move_x) / (*data)->size)] != 'p')
    || ((*data)->map->map_buffer[(int)map_grid_y][(int)map_grid_x] != '1' && 
        (*data)->map->map_buffer[(int)map_grid_y][(int)map_grid_x] != 'P'))
	{
		move_x = (*data)->move_x;
		move_y = (*data)->move_y;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data);
	}
	else
	{
		(*data)->move_x = move_x;
		(*data)->move_y = move_y;
	}
}

void	hook(mlx_key_data_t keydata, void *ml)
{
	t_config **data;
	double old_y;
	double old_x;
	double new_x;
	double new_y;
	data = ml;
	(void)keydata;
	if (mlx_is_key_down((*data)->mlx_ptr, 79))
	{
		cherch_pos_dor(data);
		printf ("x_o %d\n",(*data)->dor_x);
		printf ("y_o %d\n",(*data)->dor_y);
		if ((*data)->dor_x == -1 && (*data)->dor_y == -1)
			return ;
		(*data)->map->map_buffer[(*data)->dor_x][(*data)->dor_y] = '0';
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data);
	}
	if (mlx_is_key_down((*data)->mlx_ptr, 67))
	{
		cherch_pos_dor(data);
		printf ("x_c %d\n",(*data)->dor_x);
		printf ("y_c %d\n",(*data)->dor_y);
		if ((*data)->dor_x == -1 && (*data)->dor_y == -1)
			return ;
		(*data)->map->map_buffer[(*data)->dor_x][(*data)->dor_y] = 'P';
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data);
	}
	if (mlx_is_key_down((*data)->mlx_ptr, 256)) // exit the game
		close_window(data);
	if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_RIGHT)) // rotate right
		rotate_player(data, 1);
	if ( mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_LEFT)) // rotate left
		rotate_player(data, 0);
	old_x = ((*data)->player.x + (*data)->move_x) / (*data)->size;
	old_y = ((*data)->player.y + (*data)->move_y) / (*data)->size;
	if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_W)|| mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_UP))
	{
		new_x = ((*data)->player.x + (*data)->move_x + cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y + sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y]
			&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y]
			&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x += cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y += sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;
		}
	}
	if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_S)|| mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_DOWN)) // move down
	{
		new_x = ((*data)->player.x + (*data)->move_x - cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y - sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y]
			&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y]
			&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x -= cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y -= sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;	
		}
	}
	if (mlx_is_key_down((*data)->mlx_ptr,MLX_KEY_A))
	{
		new_x = ((*data)->player.x + (*data)->move_x + sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y - cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y]
			&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y]
			&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x += sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y -= cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;
		}
	}
	if ( mlx_is_key_down((*data)->mlx_ptr,MLX_KEY_D)) // move down
	{
		new_x = ((*data)->player.x + (*data)->move_x - sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		new_y = ((*data)->player.y + (*data)->move_y + cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED)
			/ (*data)->size;
		if ((*data)->map->map_buffer[(int)old_y]
			&& (*data)->map->map_buffer[(int)old_y][(int)new_x] != '1' && (*data)->map->map_buffer[(int)old_y][(int)new_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y]
			&& (*data)->map->map_buffer[(int)new_y][(int)old_x] != '1' && (*data)->map->map_buffer[(int)new_y][(int)old_x] != 'P'
			&& (*data)->map->map_buffer[(int)new_y][(int)new_x])
		{
			(*data)->move_x -= sin((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;
			(*data)->move_y += cos((*data)->player.angle
					+ (*data)->mouv_camera_left) * PLAYER_SPEED;
		}
	}
	move_player(data);
}

void control_mousse(void *param)
{
	t_config	**data;
	int			delta_x;
	int x;
	int y;
	data = param;
	mlx_get_mouse_pos((*data)->mlx_ptr, &x, &y);
	delta_x = x - ((*data)->width_window / 2);
	(*data)->mouv_camera_left += delta_x / 600.0;
	if ((*data)->player.angle + (*data)->mouv_camera_left >= 2 * M_PI)
		(*data)->mouv_camera_left -= 2 * M_PI;
	else if ((*data)->player.angle + (*data)->mouv_camera_left < 0)
		(*data)->mouv_camera_left += 2 * M_PI;
	mlx_set_mouse_pos((*data)->mlx_ptr, (*data)->width_window / 2,
		(*data)->height_window / 2);
	if ((*data)->img)
	mlx_delete_image((*data)->mlx_ptr, (*data)->img);
	draw_update(data);
}

void	fontion_mlx_and_draw(t_config **data)
{
	draw(data);
	mlx_key_hook((*data)->mlx_ptr, hook, data);
	mlx_set_cursor_mode((*data)->mlx_ptr, MLX_MOUSE_HIDDEN);
	mlx_loop_hook((*data)->mlx_ptr, control_mousse, data);
}

