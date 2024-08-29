/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:06:49 by ahamdi            #+#    #+#             */
/*   Updated: 2024/08/27 16:43:25 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub3d.h"
// void my_mlx_pixel_put(t_config *data, int x, int y, int color) // put the pixel
// {
// 	if (x < 0) // check the x position
// 		return ;
// 	else if (x >= data-> height_window)
// 		return ;
// 	if (y < 0) // check the y position
// 		return ;
// 	else if (y >= data-> height_window)
// 		return ;
// 	mlx_put_pixel(data->img, x, y, color); // put the pixel
// }



// void draw_floor_ceiling(t_config *data, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
// {
//  int  i;
// //  int  c;

// 	i = b_pix;
// 	while (i < data-> height_window)
// 		my_mlx_pixel_put(data, ray, i++, 0xFF0000FF); // floor
// 	i = 0;
// 	while (i < t_pix)
// 		my_mlx_pixel_put(data, ray, i++, 0x02f7b2); // ceiling
// }

// int get_color(t_config *data, int flag) // get the color of the wall
// {
// 	data->ray.ray_ngl = nor_angle(data->ray.ray_ngl); // normalize the angle
// 	if (flag == 0)
// 	{
// 		if (data->ray.ray_ngl > M_PI / 2 && data->ray.ray_ngl < 3 * (M_PI / 2))
// 			return (0xB5B5B5FF); // west wall
// 		else
// 			return (0xB5B5B5FF); // east wall
// 	}
// 	else
// 	{
// 		if (data->ray.ray_ngl > 0 && data->ray.ray_ngl < M_PI)
// 			return (0xF5F5F5FF); // south wall
// 		else
// 			return (0xF5F5F5FF); // north wall
// 	}
// }

// void draw_wall(t_config *data, int ray, int t_pix, int b_pix) // draw the wall
// {
// 	int color;

// 	color = get_color(data, data->ray.flag);
// 	while (t_pix < b_pix)
// 		my_mlx_pixel_put(data, ray, t_pix++, color);
// }

// void render_wall(t_config *data, int ray) // render the wall
// {
// 	double wall_h;
// 	double b_pix;
// 	double t_pix;

// 	data->ray.distance *= cos(nor_angle(data->ray.ray_ngl - (data->player.angle + data->mouv_camera_left))); // fix the fisheye
// 	wall_h = (data->size / data->ray.distance) * ((data-> height_window / 2) / tan(data->player.fov_rd / 2)); // get the wall height
// 	b_pix = (data-> height_window / 2) + (wall_h / 2); // get the bottom pixel
// 	t_pix = (data-> height_window / 2) - (wall_h / 2); // get the top pixel)
// 	if (b_pix > data-> height_window) // check the bottom pixel
// 		b_pix = data-> height_window;
// 	if (t_pix < 0) // check the top pixel
// 		t_pix = 0;
// 	draw_wall(data, ray, t_pix, b_pix); // draw the wall
// 	draw_floor_ceiling(data, ray, t_pix, b_pix); // draw the floor and the ceiling
// }