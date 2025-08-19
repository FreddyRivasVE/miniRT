/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_create_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:03:36 by brivera           #+#    #+#             */
/*   Updated: 2025/08/19 23:08:35 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mrt_put_color(t_vec4 color, int x, int y, t_window window)
{
	int			index;
	uint8_t		*pixels;
	t_vec4		clamped;

	clamped = vec4_clamp(color, 0.0f, 0.999f);
	index = (y * window.width + x) * 4;
	pixels = window.image->pixels;
	pixels[index] = (uint8_t)(255.99f * clamped[0]);
	pixels[index + 1] = (uint8_t)(255.99f * clamped[1]);
	pixels[index + 2] = (uint8_t)(255.99f * clamped[2]);
	pixels[index + 3] = 255;
}

t_vec4	mrt_ray_color(t_ray ray, t_data *elements)
{
	t_scene_node	*current;
	float			closest_t;
	t_vec4			hit_color;
	float			t;
	t_hittable		temp_hit;

	hit_color[0] = 0.0f; // borrar
	hit_color[1] = 0.0f; //borrar
	hit_color[2] = 0.0f; //borrar
	hit_color[3] = 0.0f; //borrar. en mi pc no compila sin inicializar antes de usar.
	closest_t = INFINITY;
	current = elements->objects;
	while (current)
	{
		if (current->type == SPHERE)
		{
			if (mrt_hit_sphere(ray, *(t_sphere *)current->object, &t)
				&& t < closest_t && t > 0.001f)
			{
				closest_t = t;
				hit_color = current->color;
			}
		}
		if (current->type == PLANE)
		{
			if (mrt_hit_plane(ray, *(t_plane *)current->object, &t)
				&& t < closest_t && t > 0.001f)
			{
				closest_t = t;
				hit_color = current->color;
			}
		}
		if (current->type == CYLINDER)
		{
			if (mrt_hit_cylinder(ray, *(t_cylinder *)current->object, &temp_hit)
				&& temp_hit.t < closest_t && temp_hit.t > 0.001f)
			{
				closest_t = temp_hit.t;
				hit_color = current->color;
			}
		}
		current = current->next;
	}
	if (closest_t == INFINITY)
		return (vec4_create(0, 0, 0, 0));
	return (hit_color);
}

t_ray	mrt_create_ray(t_vec4 origin, t_vec4 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

/*
	float u; // coordenada horizontal normalizada [0,1]
	float v; // coordenada vertical normalizada [0,1]
*/

t_ray	mrt_generate_ray(t_camera_view cam, float x, float y, t_window window)
{
	float	u;
	float	v;
	t_vec4	point_on_plane;
	t_vec4	direction;

	u = (x + 0.5f) / (float)window.width;
	v = (y + 0.5f) / (float)window.height;
	v = 1.0f - v;
	point_on_plane = cam.bottom_left_corner;
	point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.horizontal, u));
	point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.vertical, v));
	direction = vec4_normalize(vec4_sub(point_on_plane, cam.origin));
	return (mrt_create_ray(cam.origin, direction));
}

void	mrt_draw_to_window(t_window window, t_data *elements)
{
	int				j;
	int				i;
	t_camera_view	camera;
	t_ray			ray;
	t_vec4			color;

	j = 0;
	camera = mrt_compute_camera_view(elements->camera, window);
	while (j < window.height)
	{
		i = 0;
		while (i < window.width)
		{
			ray = mrt_generate_ray(camera, (float)i, (float)j, window);
			color = mrt_ray_color(ray, elements);
			mrt_put_color(color, i, j, window);
			i++;
		}
		j++;
	}
}
