/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 19:53:51 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	main(int argc, char **argv)
{
	t_app_context	app;
	t_data			elements;
	t_list			*read_file;

	if (argc != 2)
		return (ft_print_error("Error\n Incluya un archivo .rt valido"), 1);
	read_file = mrt_read_file(argv[1]);
	if (!read_file)
		return (EXIT_FAILURE);
	if (!mrt_init_scene(&elements, &read_file))
		return (mrt_clear_scene(&elements),
			ft_print_error("Error\n"), EXIT_FAILURE);
	elements.checkerboard = false;
	app.window = mrt_setup_window();
	app.elements = &elements;
	ft_putendl_fd("Renderizando escena...", 1);
	mrt_draw_to_window(app.window, app.elements);
	ft_putendl_fd("Render completado. Abriendo ventana...", 1);
	ft_putendl_fd("Presiona 'P' para alternar patron tablero de ajedrez", 1);
	mlx_image_to_window(app.window.mlx, app.window.image, 0, 0);
	mlx_key_hook(app.window.mlx, &mrt_keyfuncion, &app);
	mlx_loop(app.window.mlx);
	mrt_clear_scene(&elements);
	mlx_terminate(app.window.mlx);
	return (EXIT_SUCCESS);
}
