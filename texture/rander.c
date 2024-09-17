/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:47:43 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/16 12:55:09 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void my_mlx_pixel_put(t_config *data, double x, double y, int color) // put the pixel
{
	if (x > 0 && x < data->width_window && y < data->height_window && y > 0)
		mlx_put_pixel(data->img, x, y, color);
	
}
void draw_floor_ceiling(t_config *data, int ray, int top_pix, int min_pix)
{
	int  i;

	i = 0;
	while (i < top_pix)
		my_mlx_pixel_put(data, ray, i++, 0x89CFF3FF);
	i = min_pix;
	while (i < data->height_window)
		my_mlx_pixel_put(data, ray, i++, GREN);
}

mlx_texture_t	*get_texture_bonus(t_config **mlx, int i)
{
	(*mlx)->ray[i].ray_ngl = normalizeAngle((*mlx)->ray[i].ray_ngl);
		map_y = (int)(mlx->ray[i].horiz_y / TILE_SIZE);
    	map_x = (int)(mlx->ray[i].horiz_x / TILE_SIZE);
    	if (mlx->ray[i].flag == 1 && mlx->map->map_buffer && 
       		map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
        	mlx->map->map_buffer[map_y] &&
        	map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
        	mlx->map->map_buffer[map_y][map_x] == 'P')
        	return ((*mlx)->texture_porte);
			map_y = (int)(mlx->ray[i].vert_y / TILE_SIZE);
       		map_x = (int)(mlx->ray[i].vert_x / TILE_SIZE);
        if (mlx->ray[i].flag == 0 && mlx->map->map_buffer &&
            map_y >= 0 && map_y < mlx->map->map_height && // Vérifiez la hauteur de la carte
            mlx->map->map_buffer[map_y] &&
            map_x >= 0 && map_x < mlx->map->map_width && // Vérifiez la largeur de la carte
            mlx->map->map_buffer[map_y][map_x] == 'P')
           	return ((*mlx)->texture_porte);
	if ((*mlx)->ray[i].flag == 0)
	{
		if ((*mlx)->ray[i].ray_ngl > M_PI / 2 && (*mlx)->ray[i].ray_ngl < 3 * (M_PI / 2))
			return ((*mlx)->texture_or);
			return ((*mlx)->texture_or);
	}
	else
	{
		if ((*mlx)->ray[i].ray_ngl > 0 && (*mlx)->ray[i].ray_ngl < M_PI)
			return ((*mlx)->texture_or);
		else
			return ((*mlx)->texture_or);
	}
}
double		get_x_o(mlx_texture_t	*texture, t_config *mlx, int i)
{
	double		x_o ;
	
	if (mlx->ray[i].flag == 1)
		x_o = (int)fmodf((mlx->ray[i].horiz_x * (texture->height / TILE_SIZE)), texture->height);
	else
		x_o = (int)fmodf((mlx->ray[i].vert_y * \
		(texture->height / TILE_SIZE)), texture->height);
	return (x_o);
}

void	draw_wall(t_config *mlx, double top_pix, double min_pix, double wall_h, int i)
{
	double		x_o;
	double			y_o;
	uint32_t		*arr;
	double			y_step;
	mlx_texture_t	*texture;
	int map_y;
	int map_x;

	texture = get_texture_bonus(&mlx, i);
	if (!texture)
	{
		ft_putstr_fd("ERROR\n", 2);
		exit(0);
	}
	arr = (uint32_t *)texture->pixels;
	y_step = (double)texture->height / wall_h;
	x_o = get_x_o(texture, mlx, i);
	y_o = (top_pix - (mlx->height_window / 2) + (wall_h / 2)) * y_step;
	if (y_o < 0)
		y_o = 0;
	while (top_pix < min_pix)
	{
                mlx_put_pixel(mlx->img, i, top_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
    }
    y_o += y_step;
    top_pix++;
}

void render_wall(t_config **data) // render the wall
{
	double wall_h;
	double min_pix;
	double top_pix;
	int i;

	i = 0;
	while (i <= (*data)->width_window)
	{
		(*data)->ray[i].distance *= cos(normalizeAngle( (*data)->ray[i].ray_ngl - ((*data)->player.angle + (*data)->mouv_camera_left))); // fix the fisheye
		wall_h = ((*data)->size / (*data)->ray[i].distance) * (((*data)->width_window / 2) / tan((*data)->player.fov_rd / 2)); // get the wall height
		min_pix = ((*data)->height_window / 2) + (wall_h / 2); // get the bottom pixel
		top_pix = ((*data)->height_window/ 2) - (wall_h / 2); // get the top pixel
		if (min_pix > (*data)->height_window) // check the bottom pixel
			min_pix = (*data)->height_window;
		if (top_pix < 0) // check the top pixel
			top_pix = 0;
		(*data)->ray[i].index = i;

		draw_wall(*data,  top_pix, min_pix, wall_h, i);
		draw_floor_ceiling(*data, i, top_pix, min_pix);
		i++;
	}
}