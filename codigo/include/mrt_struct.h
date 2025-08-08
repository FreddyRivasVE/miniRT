/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:43:23 by brivera           #+#    #+#             */
/*   Updated: 2025/08/08 14:29:48 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_STRUCT_H
# define MRT_STRUCT_H

# include "MLX42/MLX42.h"

typedef float	t_vec4 __attribute__((vector_size(16)));

typedef enum s_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	AMBIENT,
	LIGHT,
	CAMERA
}	t_type;

typedef struct s_window
{
	int				width;
	int				height;
	mlx_image_t		*image;	
}	t_window;

typedef struct s_ambient
{
	float		ratio;
	t_vec4		color;
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
	t_vec4	origin;
	t_vec4	direction;
	double	fov;
}	t_camera;

typedef struct s_camera_view
{
	t_vec4	origin;
	t_vec4	horizontal;
	t_vec4	vertical;
	t_vec4	bottom_left_corner;
}	t_camera_view;

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

typedef struct s_object
{
	t_type		type;	// Tipo del objeto (esfera, plano, cilindro)
	void		*data;	// Puntero a la estructura concreta
	t_vec4		color;	// Color del objeto (RGB)
}	t_object;

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
	float	angle;
	t_vec4	n;
}	t_cylinder;

typedef struct s_hit_record
{
	t_vec4	point;		// Punto de intersección
	t_vec4	normal;		// Normal en el punto
	float	t;			// Valor de t en el rayo (distancia)
}	t_hit_record;

typedef struct s_hittable
{
	t_ray			*ray;
	float			t_min;
	float			t_max;
	t_hit_record	*rec;
}	t_hittable;

typedef struct s_scene_node
{
	t_type					type;
	void					*object; // puede ser t_sphere*, t_plane*, etc.
	t_hittable				*hit;
	t_vec4					color;
	struct s_scene_node		*next;
	struct s_scene_node		*prev;
}	t_scene_node;

typedef struct s_data
{
	t_ambient		*ambient;
	t_camera		*camera;
	t_point_light	*light;
	t_scene_node	*objects;
}	t_data;

#endif