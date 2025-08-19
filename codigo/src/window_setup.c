/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:59:34 by brivera           #+#    #+#             */
/*   Updated: 2025/08/19 23:30:33 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// En window_setup.c
t_window	mrt_setup_window(void)
{
	t_window	window;

	window.width = WIDTH;
	window.height = (int)(window.width / ASPECT_RATIO);
	// Verificación adicional
	if (window.height < 1)
		window.height = 1;
	window.mlx = mlx_init(window.width, window.height, "miniRT", false);
	window.image = mlx_new_image(window.mlx, window.width, window.height);
	return (window);
}

void	mrt_keyfuncion(mlx_key_data_t keydata, void *data)
{
	mlx_t	*mlx;

	(void)keydata;
	mlx = (mlx_t *)data;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}
