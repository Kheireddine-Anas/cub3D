/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:47:43 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/15 16:30:58 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void draw_img(t_config **data)
{
	mlx_texture_t	*texture;
	mlx_image_t *img_te;
	texture = mlx_load_png("textures/girl_with_a_pearl_earring.png");
	if (!texture)
	{
		ft_putstr_fd("error", 2);
		exit (1);
	}
	(*data)->img = mlx_texture_to_image ((*data)->mlx_ptr, texture);
	if (!(*data)->img)
	{
		ft_putstr_fd("error", 2);
		exit (1);
	}
	while (0 < 200)
	{
		mlx_put_pixel(mlx, mlx->ray->index, t_pix, reverse_bytes_bonus(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += y_step;
		t_pix++;
	}
}
