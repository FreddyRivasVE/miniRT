/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:14:15 by brivera           #+#    #+#             */
/*   Updated: 2025/07/28 20:10:54 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

//libs42
# include "../libs/libft/libft.h"
# include "MLX42/MLX42.h"

# define WIDTH 1980
# define ASPECT_RATIO 1.7777777778 // producto de 16 % 8

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

// Estructura para manejar los datos de la ventana e imagen de dibujo
typedef struct s_window
{
	int				width;
	int				height;
	mlx_image_t		*image;	
}	t_window;

/*
Definimos un tipo vectorial de 4 floats (vec4), usando extensiones de GCC/Clang.
Cada float ocupa 4 bytes, así que 4 x 4 bytes = 16 bytes en total.
El atributo vector_size(16) le dice al compilador que queremos que este tipo
se almacene y procese como un vector SIMD de 128 bits (16 bytes), lo que permite
hacer operaciones como suma, resta o multiplicación componente a componente
de manera más eficiente usando instrucciones del procesador (SIMD). */

typedef float	t_vec4 __attribute__((vector_size(16)));

typedef struct s_ambient
{
	float		ratio;	// entre 0.0 y 1.0
	t_vec4		color;	// RGB entre 0 y 255
}	t_ambient;

/*
| `ambient_ratio` | Resultado visual                          |
| --------------- | ----------------------------------------- |
| `0.0`           | Las sombras son negras, muy oscuro        |
| `0.2`           | Sombras visibles, pero aún marcadas       |
| `0.5`           | Iluminación pareja, detalles más visibles |
| `1.0`           | Todo iluminado por igual, sin sombras     |
*/

/*
 * Usamos `t_camara` para guardar los datos crudos del archivo .rt:
 *   - Posición de la cámara
 *   - Dirección hacia dónde mira
 *   - Campo de visión (fov)
 *
 * Luego convertimos eso en una `t_cam`, que contiene:
 *   - origen (orig)
 *   - vectores horizontal y vertical del viewport
 *   - esquina inferior izquierda del plano de proyección
 *
 * Esto nos permite lanzar rayos desde la cámara hacia cada píxel de la imagen.
 */

typedef struct s_camera
{
	t_vec4	origin;	// Posición de la cámara (p.ej. C -50.0,0,20)
	t_vec4	direction;	// Vector de orientación (normalizado, ej: 0.0,0.0,1.0) rango -1 a 1
	double	fov;	// Campo de visión en grados (ej: 70) rango de 0 a 180
}	t_camera;

typedef struct s_camera_view //para render
{
	t_vec4	origin;
	t_vec4	horizontal;
	t_vec4	vertical;
	t_vec4	bottom_left_corner;
}	t_camera_view;

//estructura para pensar la iluminacion de modo simple
/*
typedef struct s_light
{
	t_vec4	position;
	t_vec4	color;			// un solo color general
	float	intensity; 		// potencia total
}	t_light;
*/

// estrucutura para pensar la iluminacion con mas info
typedef struct s_point_light
{
	t_vec4	position;		// Posición 3D de la luz
	t_vec4	diff_color;		// Color de la luz difusa
	float	diff_power;		// Intensidad de la luz difusa
	t_vec4	spec_color;		// Color de la luz especular
	float	spec_power;		// Intensidad de la luz especular
}	t_point_light;
/*
| Brightness Ratio | Efecto Visual                           |
| ---------------- | --------------------------------------- |
| `0.0`            | La luz está apagada, no se ve su efecto |
| `0.3`            | Luz muy tenue, sombras suaves           |
| `0.6`            | Luz moderada, ilumina con claridad      |
| `1.0`            | Luz intensa, bordes y sombras marcados  |

*/
typedef struct s_ray
{
	t_vec4	origin;		// Punto de origen del rayo
	t_vec4	direction;	// Dirección normalizada del rayo
}	t_ray;

typedef struct s_hit_record
{
	t_vec4	point;		// Punto de intersección
	t_vec4	normal;		// Normal en el punto
	float	t;			// Valor de t en el rayo (distancia)
	t_vec4	color;		// Color del objeto impactado (opcional)
}	t_hit_record;

typedef struct s_sphere
{
	t_vec4	center;		// Centro de la esfera
	float	radius;		// Radio de la esfera
}	t_sphere;

typedef struct s_plane
{
	t_vec4	point;		// Un punto sobre el plano
	t_vec4	normal;		// Vector normal al plano
}	t_plane;

typedef struct s_cylinder
{
	t_vec4	center;		// Centro de la base
	t_vec4	axis;		// Eje (dirección) del cilindro
	float	radius;		// Radio
	float	height;		// Altura
}	t_cylinder;

typedef struct s_object
{
	t_obj_type	type;	// Tipo del objeto (esfera, plano, cilindro)
	void		*data;	// Puntero a la estructura concreta
	t_vec4		color;	// Color del objeto (RGB)
}	t_object;

typedef struct s_object_list
{
	t_object				*object;	// Objeto de la escena
	struct s_object_list	*next;
	struct s_object_list	*prev;
}	t_object_list;

/*
hay proyectos que guardan los datos en una estructura
para mantener el orden lo dejo por las dudas

typedef struct s_hit_context
{
	t_ray			*ray;    // Rayo que se lanza
	float			t_min;   // t mínimo permitido
	float			t_max;   // t máximo permitido
	t_hit_record	*rec;    // Registro del hit (si ocurre)
}	t_hit_context;

// Registro de una colisión entre un rayo y un objeto
// - p: punto exacto del impacto
// - n: vector normal en ese punto
// - t: valor del parámetro t donde ocurrió el impacto
// - front_face: indica si el impacto fue con la cara frontal
// - color: color del objeto impactado
typedef struct s_hit_record
{
	t_vec4	p;
	t_vec4	n;
	float	t;
	bool	front_face;
	t_vec4	color;
}	t_hit_record;

*/

typedef struct s_data
{
	t_ambient		*ambient;	// Luz ambiente
	t_camera		*camera;	// Cámara
	//t_point_light	*light;		// Luz puntual
	//t_object_list	*objects;	// Lista de objetos de la escena
}	t_data;

//parce
int			mrt_read_file(char *file);
//window
t_window	mrt_setup_window(mlx_t **mlx);
void		mrt_keyfuncion(mlx_key_data_t keydata, void *data);
//operaciones de vectores
t_vec4		vec4_normalize(t_vec4 v);
t_vec4		vec4_add(t_vec4 a, t_vec4 b);
t_vec4		vec4_scale(t_vec4 v, float s);
float		vec4_dot(t_vec4 a, t_vec4 b);
t_vec4		vec4_sub(t_vec4 a, t_vec4 b);
t_vec4		vec4_reflect(t_vec4 v, t_vec4 n);

#endif