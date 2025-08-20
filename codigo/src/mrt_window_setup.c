/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_window_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-20 11:01:19 by brivera           #+#    #+#             */
/*   Updated: 2025-08-20 11:01:19 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_window	mrt_setup_window(void)
{
	t_window	window;

	window.width = WIDTH;
	window.height = (int)(window.width / ASPECT_RATIO);
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
