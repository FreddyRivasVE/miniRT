/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/07/28 20:35:20 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_window	window;
	mlx_t		*mlx;

	if (argc != 2)
		return (ft_print_error("Error\nFaltan argumentos.Ejemplo:./miniRT file.rt"), 1);
	if (!mrt_read_file(argv[1]))
		return (1);
	window = mrt_setup_window(&mlx);
	mrt_draw_to_window(window);
	mlx_image_to_window(mlx, window.image, 0, 0);
	mlx_key_hook(mlx, &mrt_keyfuncion, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

