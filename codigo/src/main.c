/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 14:17:50 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_window	window;
	t_data		elements;
	t_list		*read_file;

	if (argc != 2)
		return (ft_print_error("Error\n Incluya un archivo .rt valido"), 1);
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
	ft_putendl_fd("Renderizando escena...", 1);
	mrt_draw_to_window(window, &elements);
	ft_putendl_fd("Render completado. Abriendo ventana...", 1);
	mlx_image_to_window(window.mlx, window.image, 0, 0);
	mlx_key_hook(window.mlx, &mrt_keyfuncion, window.mlx);
	mlx_loop(window.mlx);
	mrt_clear_scene(&elements);
	mlx_terminate(window.mlx);
	return (EXIT_SUCCESS);
}
