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

//borrar pero es una prueba
t_camera_view	setup_test_camera(t_window window)
{
	t_camera_view	camera;
	float			viewport_height = 2.0;
	float			viewport_width = viewport_height * ((float)window.width / window.height);
	float			focal_length = 1.0;

	t_vec4	origin = (t_vec4){0.0, 0.0, 0.0, 0.0};
	t_vec4	horizontal = (t_vec4){viewport_width, 0.0, 0.0, 0.0};
	t_vec4	vertical = (t_vec4){0.0, viewport_height, 0.0, 0.0};
	t_vec4	bottom_left_corner = origin 
		- horizontal * 0.5 
		- vertical * 0.5 
		- (t_vec4){0.0, 0.0, focal_length, 0.0};
	camera.origin = origin;
	camera.horizontal = horizontal;
	camera.vertical = vertical;
	camera.bottom_left_corner = bottom_left_corner;
	return (camera);
}

// vec_utils.c // cuentas que hay que hacer 
// Escala un vector por un escalar: v * s
t_vec4	vec4_scale(t_vec4 v, float s)
{
	return ((t_vec4){v[0] * s, v[1] * s, v[2] * s, v[3] * s});
}

// Suma de vectores: a + b
t_vec4	vec4_add(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]});
}

// Normaliza un vector
t_vec4	vec4_normalize(t_vec4 v)
{
	float	len;

	len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (len == 0.0f)
		return ((t_vec4){0, 0, 0, 0});
	return ((t_vec4){v[0] / len, v[1] / len, v[2] / len, v[3]});
}

// Crea un rayo con un origen y una dirección específicos
t_ray	mrt_create_ray(t_vec4 origin, t_vec4 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

// Genera un rayo desde la cámara hacia un píxel específico (i, j) en la ventana
t_ray	mrt_generate_camera_ray(t_camera_view camera, float pixel_x, float pixel_y, t_window window)
{
	float	normalized_x;
	float	normalized_y;
	t_vec4	image_point;
	t_vec4	ray_dir;

	normalized_x = pixel_x / (window.width - 1);
	normalized_y = pixel_y / (window.height - 1);
	image_point = camera.bottom_left_corner +\
			(normalized_x * camera.horizontal)\
			 + (normalized_y * camera.vertical);
	ray_dir = image_point - camera.origin;
	return (mrt_create_ray(camera.origin, ray_dir));
}

// Devuelve el color del cielo en función de la dirección del rayo
t_vec4	mrt_ray_color(t_ray ray, t_data *elements)
{
	t_vec4	unit_dir;
	float	t;
	t_vec4	white;
	t_vec4	blue;

	(void)elements;
	unit_dir = vec4_normalize(ray.direction);
	t = 0.5f * (unit_dir[1] + 1.0f);  // componente Y del vector
	white = (t_vec4){1.0f, 1.0f, 1.0f, 0.0f}; // blanco
	blue = (t_vec4){0.5f, 0.7f, 1.0f, 0.0f};  // azul cielo
	return (vec4_add(vec4_scale(white, 1.0f - t), vec4_scale(blue, t)));
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
 * Esto coloca cada componente en su posición correspondiente
 * dentro del entero de 32 bits:
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
 * @param color Vector t_vec4 con los componentes R, G, B
 * (el 4to valor se ignora pero es el canal de opacidad)
 * @param x Posición horizontal del pixel
 * @param y Posición vertical del pixel
 * @param window Estructura de ventana que contiene
 * la imagen donde se va a dibujar
 *  Se usa 255.99 en lugar de 255.0 para evitar un borde en el redondeo:
	sin ese .99, un valor como 0.999 podría truncarse a 254 en lugar de 255.
 */
void	mrt_put_color(t_vec4 color, int x, int y, t_window window)
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
	int				j;
	int				i;
	t_vec4			color;
	t_camera_view	camera;
	t_ray			ray;

	camera = setup_test_camera(window);
	j = 0;
	while (j < window.height)
	{
		i = 0;
		while (i < window.width)
		{
			ray = mrt_generate_camera_ray(camera, i, j, window);
			color = mrt_ray_color(ray, NULL);
			mrt_put_color(color, i, j, window);
			i++;
		}
		j++;
	}
}


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
