/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:18:40 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/27 12:40:47 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_intalis(t_config **data)
{
	ft_putstr_fd("Failed to initialize mlx.\n", 2);
	destroy_data(data);
	exit(1);
}

void	leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_config	*data;
	int			i;

	i = 0;
	atexit(leaks);
	data = ft_calloc(1, sizeof(t_config));
	if (!data)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		exit(1);
	}
	chek_argument_and_extention(ac, av[1]);
	struct_instialisation(&data, av[1]);
	map_inistialisation(&data);
	destroy_data(&data);
	if (!(data->mlx_ptr = mlx_init(data->width_window, data->height_window,
				"cub_3d", true)))
		error_intalis(&data);
	data->rays = ft_calloc(data->width_window, sizeof(t_ray));
	if (!data->rays)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		destroy_data(&data);
		exit(1);
	}
	fontion_mlx_and_draw(&data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}
