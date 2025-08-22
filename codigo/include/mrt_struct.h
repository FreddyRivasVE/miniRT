/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:43:23 by brivera           #+#    #+#             */
/*   Updated: 2025/08/18 13:23:17 by frivas           ###   ########.fr       */
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
	mlx_t			*mlx;
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

typedef struct s_light
{
	t_vec4	position;
	t_vec4	color;
	float	brightness_r;
}	t_light;

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
	t_vec4	origin;
	t_vec4	direction;
}	t_ray;

typedef struct s_material
{
	t_vec4	base_color;
	float	ambient_coeff;		// Coeficiente de iluminación ambiente
	float	diffuse_coeff;		// Coeficiente de iluminación difusa
	float	specular_coeff;		// Coeficiente de iluminación especular
	float	shininess;			// Exponente especular (controla el brillo)
}	t_material;

typedef struct s_hittable
{
	t_vec4			point;
	t_vec4			normal;
	t_material		*material;
	float			t;
}	t_hittable;

typedef struct s_sphere
{
	t_vec4	center;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec4	point;
	t_vec4	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec4	center;
	t_vec4	axis;
	float	radius;
	float	height;
}	t_cylinder;

typedef struct s_scene_node
{
	t_type					type;
	void					*object;
	t_hittable				*hit;
	struct s_scene_node		*next;
}	t_scene_node;

typedef struct s_data
{
	t_ambient		*ambient;
	t_camera		*camera;
	t_light			*light;
	t_scene_node	*objects;
}	t_data;

#endif