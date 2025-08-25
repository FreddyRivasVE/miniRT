/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-25 12:28:11 by brivera           #+#    #+#             */
/*   Updated: 2025-08-25 12:28:11 by brivera          ###   ########.fr       */
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

t_vec4	mrt_ray_color(t_ray *ray, t_data *elements)
{
	t_scene_node	*current;
	t_vec4			hit_color;
	float			t_final;

	hit_color = (t_vec4){0, 0, 0, 0};
	t_final = INFINITY;
	current = elements->objects;
	while (current)
	{
		if (current->type == SPHERE)
		{
			if (mrt_hit_sphere(ray, *(t_sphere *)current->object, &current->hit)
				&& current->hit->t < t_final && current->hit->t > EPSILON)
			{
				t_final = current->hit->t;
				hit_color = mrt_light_color(elements, current->hit, ray);
			}
		}
		if (current->type == PLANE)
		{
			if (mrt_hit_plane(ray, *(t_plane *)current->object, &current->hit)
				&& current->hit->t < t_final && current->hit->t > EPSILON)
			{
				t_final = current->hit->t;
				hit_color = mrt_light_color(elements, current->hit, ray);
			}
		}
		if (current->type == CYLINDER)
		{
			if (mrt_hit_cylinder(ray, *(t_cylinder *)current->object, &current->hit)
				&& current->hit->t < t_final && current->hit->t > EPSILON)
			{
				t_final = current->hit->t;
				hit_color = mrt_light_color(elements, current->hit, ray);
			}
		}
		current = current->next;
	}
	return (hit_color);
}

t_ray	mtr_create_ray(t_vec4 origen, t_vec4 direction)
{
	t_ray	ray;

	ray.direction = direction;
	ray.origin = origen;
	return (ray);
}

t_ray	mrt_generate_ray(t_camera_view cam, float x, float y, t_window window)
{
	t_vec4	point_on_plane;
	t_vec4	direction;
	float	u;
	float	v;

	u = (float)(x + 0.5f) / (float)(window.width - 1);
	v = (float)(y + 0.5f) / (float)(window.height - 1);
	v = 1.0f - v;
	u = 1.0f - u;
	point_on_plane = cam.bottom_left_corner;
	point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.horizontal, u));
	point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.vertical, v));
	direction = vec4_normalize(vec4_sub(point_on_plane, cam.origin));
	return (mtr_create_ray(cam.origin, direction));
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
			color = mrt_ray_color(&ray, elements);
			mrt_put_color(color, i, j, window);
			i++;
		}
		j++;
	}
}
