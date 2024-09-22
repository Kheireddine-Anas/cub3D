/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:49 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/21 18:31:29 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	my_mlx_pixel_put(t_config *data, double x, double y, int color)
		// put the pixel
{
	if (x < 0 || x > data->width_window || y > data->height_window || y < 0)
		return ;
	mlx_put_pixel(data->img, x, y, color);
}
void	draw_floor_ceiling(t_config *data, int ray, int top_pix, int min_pix)
{
	int	i;

	i = 0;
	while (i < top_pix)
		my_mlx_pixel_put(data, ray, i++, 0x89CFF3FF);
	i = min_pix;
	while (i < data->height_window)
		my_mlx_pixel_put(data, ray, i++, GREN);
}

mlx_texture_t	*get_texture_bonus(t_config *mlx, int flag)
{
	int				map_y;
	int				map_x;
	mlx->ray.ray_ngl = normalizeAngle(mlx->ray.ray_ngl);
	if (flag == 0)
	{
		map_y = (int)floor(mlx->ray.vert_y / TILE_SIZE);
       	map_x = (int)floor(mlx->ray.vert_x / TILE_SIZE);
		if (mlx->ray.ray_ngl > M_PI / 2 && mlx->ray.ray_ngl < 3 * (M_PI / 2))
		{
        	if ( mlx->map->map_buffer &&
            	map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
            	mlx->map->map_buffer[map_y] &&
            	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
            	mlx->map->map_buffer[map_y][map_x] == 'P')
           			return (mlx->texture_close_dor);
			else if ( mlx->map->map_buffer &&
            	map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
            	mlx->map->map_buffer[map_y] &&
            	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
            	mlx->map->map_buffer[map_y][map_x] == 'K')
           			return (mlx->texture_s);
			else if ( mlx->map->map_buffer &&
            	map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
            	mlx->map->map_buffer[map_y] &&
            	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
            	mlx->map->map_buffer[map_y][map_x] == '4')
			{
				return (mlx->texture_close_dor);
			}
			else
				return (mlx->texture_or);
		}
		else
		{
			if ( mlx->map->map_buffer &&
            	map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
            	mlx->map->map_buffer[map_y] &&
            	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
            	mlx->map->map_buffer[map_y][map_x] == 'P')
           			return (mlx->texture_close_dor);
			else if ( mlx->map->map_buffer &&
            	map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
            	mlx->map->map_buffer[map_y] &&
            	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
            	mlx->map->map_buffer[map_y][map_x] == 'K')
           			return (mlx->texture_s);
			else if ( mlx->map->map_buffer &&
            	map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
            	mlx->map->map_buffer[map_y] &&
            	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
            	mlx->map->map_buffer[map_y][map_x] == '4')
			{
				return (mlx->texture_close_dor);
			}
			else
				return (mlx->texture_or);
		}
	}
	else
	{
		map_y = (int)floor(mlx->ray.horiz_y / TILE_SIZE);
    	map_x = (int)floor(mlx->ray.horiz_x / TILE_SIZE);
		if (mlx->ray.ray_ngl > 0 && mlx->ray.ray_ngl < M_PI)
		{
			if ( mlx->map->map_buffer &&
       		map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
        	mlx->map->map_buffer[map_y] &&
        	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
        	mlx->map->map_buffer[map_y][map_x] == 'P')
        		return (mlx->texture_close_dor);
			else if ( mlx->map->map_buffer &&
       		map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
        	mlx->map->map_buffer[map_y] &&
        	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
        	mlx->map->map_buffer[map_y][map_x] == 'K')
        		return (mlx->texture_s);
			else if ( mlx->map->map_buffer &&
       		map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
        	mlx->map->map_buffer[map_y] &&
        	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
        	mlx->map->map_buffer[map_y][map_x] == '4')
			{
				return (mlx->texture_open_dor);
			}
			else
				return (mlx->texture_ver);
		}
		else
		{
			if ( mlx->map->map_buffer &&
       		map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
        	mlx->map->map_buffer[map_y] &&
        	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
        	mlx->map->map_buffer[map_y][map_x] == 'P')
        		return (mlx->texture_close_dor);
			else if ( mlx->map->map_buffer &&
       		map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
        	mlx->map->map_buffer[map_y] &&
        	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
        	mlx->map->map_buffer[map_y][map_x] == 'K')
        		return (mlx->texture_s);
			else if ( mlx->map->map_buffer &&
       		map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
        	mlx->map->map_buffer[map_y] &&
        	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
        	mlx->map->map_buffer[map_y][map_x] == '4')
			{
				return (mlx->texture_open_dor);
			}
			else
				return (mlx->texture_ver);
		}
	}
}
double	get_x_o(mlx_texture_t *texture, t_config *mlx)
{
	double	x_o;

	if (mlx->ray.flag == 1)
		x_o = (int)fmodf((mlx->ray.horiz_x * (texture->width / TILE_SIZE)),
				texture->width);
	else
		x_o = (int)fmodf((mlx->ray.vert_y * (texture->width / TILE_SIZE)),
				texture->width);
	return (x_o);
}

void	draw_wall(t_config *mlx, double top_pix, double min_pix, double wall_h)
{
	double			x_o;
	double			y_o = 0;
	uint32_t		*arr;
	double			y_step;
	mlx_texture_t	*texture;
	
	texture = get_texture_bonus(mlx, mlx->ray.flag);
	arr = (uint32_t *)texture->pixels;
	y_step = (double)texture->height / wall_h;
	x_o = get_x_o(texture, mlx);
	y_o = (top_pix - (mlx->height_window / 2) + (wall_h / 2)) * y_step;
	if (y_o < 0)
		y_o = 0;
	while (top_pix < min_pix)
	{
		mlx_put_pixel(mlx->img, mlx->ray.index, top_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += y_step;
		top_pix++;
	}
}

void	render_wall(t_config **data, int ray, double distance, double angle)
		// render the wall
{
	double wall_h;
	double min_pix;
	double top_pix;
	(void)angle;
	distance *= cos(normalizeAngle(angle - ((*data)->player.angle
					+ (*data)->mouv_camera_left))); // fix the fisheye
	
	(*data)->ray.distance = distance;
	wall_h = ((*data)->size / distance) * (((*data)->width_window / 2)
			/ tan((*data)->player.fov_rd / 2)); // get the wall height
	min_pix = ((*data)->height_window / 2) + (wall_h
			/ 2);                                                
		// get the bottom pixel
	top_pix = ((*data)->height_window / 2) - (wall_h
			/ 2);                                                
		// get the top pixel
	if (min_pix > (*data)->height_window)                                                                 
		// check the bottom pixel
		min_pix = (*data)->height_window;
	if (top_pix < 0) // check the top pixel
		top_pix = 0;
	(*data)->ray.index = ray;
	draw_wall(*data, top_pix, min_pix, wall_h);
	draw_floor_ceiling(*data, ray, top_pix, min_pix);
}