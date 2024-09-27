/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kebord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:49:12 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/25 17:50:57 by ahamdi           ###   ########.fr       */
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

int	open_close_door(t_config **data)
{
	if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_O))
	{
		chek_door(data);
		if ((*data)->dor_x == -1 && (*data)->dor_y == -1)
			return(1);
		else if ((*data)->dor_y != 0 && (*data)->dor_x != (*data)->map->map_width -1 && (*data)->dor_y != (*data)->map->map_height -1)
		{
			(*data)->map->map_buffer[(*data)->dor_y][(*data)->dor_x] = '4';
			mlx_delete_image((*data)->mlx_ptr, (*data)->img);
			draw_update(data, (*data)->texture_r);
		}
		return (1);
	}
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_C))
	{
		chek_door(data);
		if ((*data)->dor_x == -1 && (*data)->dor_y == -1)
			return (1);
		else if ((*data)->dor_y != 0 && (*data)->dor_x != (*data)->map->map_width -1 && (*data)->dor_y != (*data)->map->map_height -1)
		{
			(*data)->map->map_buffer[(*data)->dor_y][(*data)->dor_x] = 'P';
			mlx_delete_image((*data)->mlx_ptr, (*data)->img);
			draw_update(data, (*data)->texture_r);
		}
		return (1);
	}
	return (0);
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
		draw_update(data, (*data)->texture_r);
	}
	else
	{
		(*data)->move_x = move_x;
		(*data)->move_y = move_y;
	}
}

void	hook(void *ml)
{
	t_config **data;
	double old_y;
	double old_x;
	double new_x;
	double new_y;
	data = ml;
	int pid;

	old_x = ((*data)->player.x + (*data)->move_x) / (*data)->size;
	old_y = ((*data)->player.y + (*data)->move_y) / (*data)->size;
	control_mousse(data);
	if (mlx_is_mouse_down((*data)->mlx_ptr, MLX_MOUSE_BUTTON_LEFT))
	{
		pid = fork();
		if (pid == 0)
		{
			system("afplay textures/music_gunshot.mp3");
			usleep(100000);
			exit(0);
		}
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data, (*data)->texture_pa);
		draw_enter(*data, (*data)->texture_toush);
		return;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data, (*data)->texture_r);
		return;
	}
	else if (open_close_door(data) == 1)
		return;
	else if (mlx_is_key_down((*data)->mlx_ptr, 256)) // exit the game
		close_window(data);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_RIGHT)) // rotate right
		rotate_player(data, 1);
	else if ( mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_LEFT)) // rotate left
		rotate_player(data, 0);
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_W)|| mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_UP))
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
	else if (mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_S)|| mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_DOWN)) // move down
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
	else if (mlx_is_key_down((*data)->mlx_ptr,MLX_KEY_A))
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
	else if ( mlx_is_key_down((*data)->mlx_ptr,MLX_KEY_D)) // move down
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
void animation(mlx_key_data_t keydata, void* param)
{
	t_config **data;
	int pid;
	data = param;
	if (keydata.key == MLX_KEY_SPACE)
	{
		pid = fork();
		if (pid == 0)
		{
			system("afplay textures/music_gunshot.mp3");
			exit(0);
		}
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data, (*data)->texture_pa);
		draw_enter(*data, (*data)->texture_toush);
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw_update(data, (*data)->texture_r);
	}
}
void control_mousse(t_config	**data)
{
	int			delta_x;
	int x;
	int y;
	mlx_get_mouse_pos((*data)->mlx_ptr, &x, &y);
	delta_x = x - ((*data)->width_window / 2);
	(*data)->mouv_camera_left += delta_x / 600.0;
	if ((*data)->player.angle + (*data)->mouv_camera_left >= 2 * M_PI)
		(*data)->mouv_camera_left -= 2 * M_PI;
	else if ((*data)->player.angle + (*data)->mouv_camera_left < 0)
		(*data)->mouv_camera_left += 2 * M_PI;
	mlx_set_mouse_pos((*data)->mlx_ptr, (*data)->width_window / 2,
		(*data)->height_window / 2);
}

void	fontion_mlx_and_draw(t_config **data)
{
	draw(data, (*data)->texture_r);
	mlx_loop_hook((*data)->mlx_ptr, hook, data);
	// mlx_key_hook((*data)->mlx_ptr, animation, data);
	mlx_set_cursor_mode((*data)->mlx_ptr, MLX_MOUSE_HIDDEN);
}

