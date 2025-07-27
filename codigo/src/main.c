/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/07/27 12:40:15 by brivera          ###   ########.fr       */
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

	(void)keydata;  // para evitar warning
	mlx = (mlx_t *)data;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

/**
 * Crea un color en formato RGBA codificado en un solo entero de 32 bits.
 *
 * @param r Componente rojo (0-255)
 * @param g Componente verde (0-255)
 * @param b Componente azul (0-255)
 * @param a Componente alfa (0-255)
 * @return Entero de 32 bits representando el color RGBA
 * 
 * Esto coloca cada componente en su posición correspondiente dentro del entero de 32 bits:
	r << 24 → mueve el rojo 24 bits a la izquierda → ocupa los 8 bits más altos
	g << 16 → mueve el verde 16 bits a la izquierda
	b << 8 → mueve el azul 8 bits a la izquierda
	a → se queda en los 8 bits más bajos (sin desplazamiento)
 */
int	create_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	clamp_float(float x, float min, float max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

/**
 * Escribe un color en el pixel (x, y) de la imagen, convirtiendo valores
 * flotantes de color en el rango [0.0, 1.0] a enteros [0, 255].
 *
 * @param color Vector t_vec4 con los componentes R, G, B (el 4to valor se ignora)
 * @param x Posición horizontal del pixel
 * @param y Posición vertical del pixel
 * @param window Estructura de ventana que contiene la imagen donde se va a dibujar
 *  Se usa 255.99 en lugar de 255.0 para evitar un borde en el redondeo:
	sin ese .99, un valor como 0.999 podría truncarse a 254 en lugar de 255.
 */
void	mrt_write_color(t_vec4 color, int x, int y, t_window window)
{
	int	read_int;
	int	green_int;
	int	blue_int;

	read_int = (int)(255.99 * clamp_float(color[0], 0, 0.999));
	green_int = (int)(255.99 * clamp_float(color[1], 0, 0.999));
	blue_int = (int)(255.99 * clamp_float(color[2], 0, 0.999));
	mlx_put_pixel(window.image, x, window.height - y - 1, create_rgba(read_int, green_int, blue_int, 255));
}

void	mrt_draw_to_window(t_window window)
{
	int		j;
	int		i;
	t_vec4	color;

	j = 0;
	while (j < window.height)
	{
		i = 0;
		while (i < window.width)
		{
			color[0] = 0.90;	// rojo
			color[1] = (float)j / (float)window.height;	// verde
			color[2] = 0.50;							// azul fijo
			color[3] = 0.0;								// canal alfa (sin usar ahora)
			mrt_write_color(color, i, j, window);
			i++;
		}
		j++;
	}
}
/*
void	mrt_draw_to_window(t_window window)
{
	int		j;
	int		i;
	t_vec4	color;

	j = 0;
	while (j < window.height)
	{
		i = 0;
		while (i < window.width)
		{
			if (j < window.height / 3)
			{
				// Franja superior - celeste
				color[0] = 0.53; // R
				color[1] = 0.81; // G
				color[2] = 0.92; // B
			}
			else if (j < 2 * window.height / 3)
			{
				// Franja del medio - blanco
				color[0] = 1.0;
				color[1] = 1.0;
				color[2] = 1.0;
			}
			else
			{
				// Franja inferior - celeste
				color[0] = 0.53;
				color[1] = 0.81;
				color[2] = 0.92;
			}
			color[3] = 0.0; // Canal alfa (sin usar por ahora)
			mrt_write_color(color, i, j, window);
			i++;
		}
		j++;
	}
}*/

int	main(int argc, char **argv)
{
	t_window	window;
	mlx_t		*mlx;

	if (argc != 2)
		return (ft_print_error("Error\nFaltan argumentos!.Ejemplo:./miniRT file.rt"), 1);
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
