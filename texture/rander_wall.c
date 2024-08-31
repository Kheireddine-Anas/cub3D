/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:49 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/31 13:02:06 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	reverse_bytes_bonus(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}
void	my_mlx_pixel_put_bonus(t_config *data, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >=data->width_window)
		return ;
	if (y < 0)
		return ;
	else if (y >= data->height_window)
		return ;
	mlx_put_pixel(data->img, x, y, color);
}
void my_mlx_pixel_put(t_config *data, int x, int y, int color) // put the pixel
{
	if (x < 0 || x >= data->width_window || y >= data->height_window || y < 0)
		return ;
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


int get_color(t_config *data, int flag)
{
	data->ray.ray_ngl = normalizeAngle(data->ray.ray_ngl);
	if (flag == 0)
	{
		if (data->ray.ray_ngl > M_PI / 2 && data->ray.ray_ngl < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (data->ray.ray_ngl > 0 && data->ray.ray_ngl < M_PI)
			return (BLK); // south wall
		else
			return (BLK); // north wall
	}
}
double	get_x_o_bonus(mlx_texture_t	*texture, t_config *data)
{
	double	x_o;

	if (data->ray.flag == 1)
		x_o = (int)fmodf((data->ray.horiz_x * \
		(texture->width / TILE_SIZE_R)), texture->width);
	else
		x_o = (int)fmodf((data->ray.vert_y * \
		(texture->width / TILE_SIZE_R)), texture->width);
	return (x_o);
}
void	draw_wall_bonus(t_config *data, int t_pix, int b_pix, double wall_h)
{
	// double			x_o;
	// double			y_o;
	// mlx_texture_t	*texture;
	// uint32_t		*arr;
	// double			y_step;
	(void) wall_h;
	// uint32_t i =0;
	// // texture = mlx_load_png("img/Mona_Lisa.png");
	// arr = (uint32_t *)texture->pixels;
	// y_step = (double)texture->height / wall_h;
	// x_o = texture->width ;
	// y_o = texture->height;
	// if (y_o < 0)
	// 	y_o = 0;
	
	while (t_pix < b_pix )
	{
		my_mlx_pixel_put_bonus(data, data->ray.index, t_pix, RED);

		// y_o += y_step;
		// i++;
		t_pix++;
	}
}

void render_wall(t_config **data, int ray, double distance,  double angle) // render the wall
{
	double wall_h;
	double min_pix;
	double top_pix;

	distance *= cos(normalizeAngle( angle - ((*data)->player.angle + (*data)->mouv_camera_left))); // fix the fisheye
	(*data)->ray.distance = distance;
	wall_h = (32 / distance) * (((*data)->width_window / 2) / tan((*data)->player.fov_rd / 2)); // get the wall height
	min_pix = ((*data)->height_window / 2) + (wall_h / 2); // get the bottom pixel
	top_pix = ((*data)->height_window/ 2) - (wall_h / 2); // get the top pixel
	if (min_pix > (*data)->height_window) // check the bottom pixel
		min_pix = (*data)->height_window;
	if (top_pix < 0) // check the top pixel
		top_pix = 0;
	(*data)->ray.index = ray;
	draw_wall_bonus(*data,  top_pix, min_pix,wall_h);
	draw_floor_ceiling(*data, ray, top_pix, min_pix);
}