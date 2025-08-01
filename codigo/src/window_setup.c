/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:59:34 by brivera           #+#    #+#             */
/*   Updated: 2025/07/28 20:00:34 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_window	mrt_setup_window(mlx_t **mlx)
{
	t_window	window;

	window.width = WIDTH;
	window.height = (int)(window.width / ASPECT_RATIO);
	*mlx = mlx_init(window.width, window.height, "miniRT", false);
	window.image = mlx_new_image(*mlx, window.width, window.height);
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
