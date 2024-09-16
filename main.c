/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdi <ahamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:18:40 by ahamdi            #+#    #+#             */
/*   Updated: 2024/09/15 10:08:16 by ahamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_intalis(t_config **data)
{
	ft_putstr_fd("Failed to initialize mlx.\n", 2);
	destroy_data(data);
	exit(1);
}

int	main(int ac, char **av)
{
	t_config	*data;
	int			i;

	i = 0;
	// atexit(leaks);
	data = ft_calloc(1, sizeof(t_config));
	chek_argument_and_extention(ac, av[1]);
	struct_instialisation(&data, av[1]);
	map_inistialisation(&data);
	if (!(data->mlx_ptr = mlx_init(data->width_window, data->height_window, "cub_3d", true)))
		error_intalis(&data);
	fontion_mlx_and_draw(&data);
	mlx_loop(data->mlx_ptr);
	mlx_terminate(data->mlx_ptr);
}
