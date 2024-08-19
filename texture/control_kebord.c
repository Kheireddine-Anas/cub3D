/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_kebord.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:49:12 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/18 13:26:50 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	contro_(int key, t_config **data, double angle_rad)
{
	(void)angle_rad;
	if (key == MLX_KEY_A)
	{
		(*data)->mouve_palyer_left -= MOVE_STEP;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw(data);
		(*data)->mouv_left = 0;
	}
	if (key == MLX_KEY_D)
	{
		(*data)->mouve_palyer_left += MOVE_STEP;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw(data);
		(*data)->mouv_rigt = 0;
	}
	if (key == MLX_KEY_RIGHT)
	{
		(*data)->mouv_camera_left += 0.2;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw(data);
	}
	if (key == MLX_KEY_LEFT)
	{
		(*data)->mouv_camera_left -= 0.2;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw(data);
	}
}

void	key_press(mlx_key_data_t keydata, void *param)
{
	t_config	**data;
	double		angle_rad;
	int			i;
	int			j;

	i = 0;
	j = 0;
	data = (t_config **)param;
	if (keydata.key == 256)
	{
		close_window(data);
		return ;
	}
	angle_rad = (*data)->player.angle;
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN
		|| mlx_is_key_down((*data)->mlx_ptr, MLX_KEY_DOWN))
	{
		i = (((*data)->player.x + ((*data)->mouve_palyer_left - (MOVE_STEP
							* cos(angle_rad))))) / (*data)->size;
		j = (((*data)->player.y + ((*data)->mouve_palyer_haut) - (MOVE_STEP
						* sin(angle_rad)))) / (*data)->size;
		if ((*data)->map->map_buffer[j]
			&& (*data)->map->map_buffer[j][i] != '1')
		{
			(*data)->mouve_palyer_left -= MOVE_STEP * cos(angle_rad);
			(*data)->mouve_palyer_haut -= MOVE_STEP * sin(angle_rad);
			mlx_delete_image((*data)->mlx_ptr, (*data)->img);
			draw(data);
		}
	}
	else if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
	{
		i = (((*data)->player.x + ((*data)->mouve_palyer_left + (MOVE_STEP
							* cos(angle_rad))))) / (*data)->size;
		j = (((*data)->player.y + ((*data)->mouve_palyer_haut) + (MOVE_STEP
						* sin(angle_rad)))) / (*data)->size;
		if ((*data)->map->map_buffer[j]
			&& (*data)->map->map_buffer[j][i] != '1')
		{
			(*data)->mouve_palyer_left += MOVE_STEP * cos(angle_rad);
			(*data)->mouve_palyer_haut += MOVE_STEP * sin(angle_rad);
			mlx_delete_image((*data)->mlx_ptr, (*data)->img);
			draw(data);
		}
	}
	else if (keydata.key == MLX_KEY_LEFT)
	{
		(*data)->mouv_camera_left -= ROTATION_ANGLE;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw(data);
	}
	else if (keydata.key == MLX_KEY_RIGHT)
	{
		(*data)->mouv_camera_left += ROTATION_ANGLE;
		mlx_delete_image((*data)->mlx_ptr, (*data)->img);
		draw(data);
	}
	else
		contro_(keydata.key, data, angle_rad);
}

void	fontion_mlx_and_draw(t_config **data)
{
	draw(data);
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_key_hook((*data)->mlx_ptr, key_press, data);
}
