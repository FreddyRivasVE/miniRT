/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/08/07 11:49:07 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_window	window;
	t_data		elements;
	t_list		*read_file;

	if (argc != 2)
		return (ft_print_error("Error\nEjemplo:./miniRT file.rt"), 1);
	read_file = mrt_read_file(argv[1]);
	if (!read_file)
		return (EXIT_FAILURE);
	if (!mrt_init_scene(&elements, &read_file))
	{
		mrt_clear_scene(&elements);
		ft_print_error("Error\n");
		return (EXIT_FAILURE);
	}
	window = mrt_setup_window();
	mrt_draw_to_window(window, &elements);
	mlx_image_to_window(window.mlx, window.image, 0, 0);
	mlx_key_hook(window.mlx, &mrt_keyfuncion, window.mlx);
	mlx_loop(window.mlx);
	mrt_clear_scene(&elements);
	mlx_terminate(window.mlx);
	return (EXIT_SUCCESS);
}
