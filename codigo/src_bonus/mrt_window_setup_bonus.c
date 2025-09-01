/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_window_setup_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:01:19 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 19:53:53 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
	t_app_context	*app;

	app = (t_app_context *)data;
	if (mlx_is_key_down(app->window.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->window.mlx);
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		app->elements->checkerboard = !app->elements->checkerboard;
		if (app->elements->checkerboard)
			ft_putendl_fd("Patron tablero de ajedrez: ACTIVADO", 1);
		else
			ft_putendl_fd("Patron tablero de ajedrez: DESACTIVADO", 1);
		ft_putendl_fd("Renderizando escena nuevamente...", 1);
		mrt_draw_to_window(app->window, app->elements);
		ft_putendl_fd("Render completado!", 1);
	}
}
