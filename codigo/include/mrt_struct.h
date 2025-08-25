/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:43:23 by brivera           #+#    #+#             */
/*   Updated: 2025/08/25 21:00:36 by brivera          ###   ########.fr       */
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
	t_vec4	dir;
	float	dist;
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
	t_vec4	ambient;
	t_vec4	diffuse;
	t_vec4	specular;
	float	diff_intensity;
	float	spec_intensity;
	float	shininess;
}	t_material;

typedef struct s_cylinder_hits
{
	t_vec4	normal_body;
	t_vec4	normal_cap_base;
	t_vec4	normal_cap_top;
	float	t_body;
	float	t_cap_base;
	float	t_cap_top;
	bool	hit_body;
	bool	hit_cap_base;
	bool	hit_cap_top;
}	t_cylinder_hits;

typedef struct s_hit
{
	t_vec4			point;
	t_vec4			normal;
	t_material		*material;
	float			t;
	float			t_closest;
}	t_hit;

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
	t_type				type;
	void				*object;
	t_hit				*hit;
	struct s_scene_node	*next;
}	t_scene_node;

typedef struct s_data
{
	t_ambient		*ambient;
	t_camera		*camera;
	t_light			*light;
	t_scene_node	*objects;
}	t_data;

typedef struct s_hit_context
{
	t_ray		*ray;
	t_data		*elements;
	t_vec4		*h_color;
	float		*t_closest;
}	t_hit_context;

#endif