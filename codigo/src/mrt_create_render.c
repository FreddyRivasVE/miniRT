/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_create_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:03:36 by brivera           #+#    #+#             */
/*   Updated: 2025/08/06 22:02:45 by brivera          ###   ########.fr       */
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
	t_vec4			final_color = vec4_create(0, 0, 0, 0);
	float			closest_t = INFINITY;
	t_sphere		*hit_sphere = NULL;
	t_vec4			hit_color;
	float			t;

	current = elements->objects;
	while (current)
	{
		if (current->type == SPHERE)
		{
			if (mrt_hit_sphere(ray, *(t_sphere *)current->object, &t) && t < closest_t)
			{
				closest_t = t;
				hit_sphere = (t_sphere *)current->object;
				hit_color = current->color;
			}
		}
		current = current->next;
	}
	if (!hit_sphere)
		return (vec4_create(0, 0, 0, 0)); // fondo negro
	// Iluminación
	t_vec4 hit_point = vec4_add(ray.origin, vec4_scale(ray.direction, closest_t));
	t_vec4 normal = vec4_normalize(vec4_sub(hit_point, hit_sphere->center));
	t_vec4 light_dir = vec4_normalize(vec4_sub(elements->light->position, hit_point));
	float diff_intensity = fmaxf(0.0f, vec4_dot(normal, light_dir)) * elements->light->diff_power;
	t_vec4 diff = vec4_scale(elements->light->diff_color, diff_intensity);

	t_vec4 view_dir = vec4_normalize(vec4_sub(ray.origin, hit_point));
	t_vec4 reflect_dir = vec4_reflect(vec4_scale(light_dir, -1.0f), normal);
	float shininess = 32.0f;
	float spec_intensity = powf(fmaxf(0.0f, vec4_dot(view_dir, reflect_dir)), shininess) * elements->light->spec_power;
	t_vec4 spec = vec4_scale(elements->light->spec_color, spec_intensity);

	t_vec4 ambient = vec4_scale(elements->ambient->color, elements->ambient->ratio);

	final_color = vec4_mul(hit_color, ambient);
	final_color = vec4_add(final_color, vec4_mul(hit_color, diff));
	final_color = vec4_add(final_color, spec);

	return (vec4_clamp(final_color, 0.0f, 1.0f));
}



t_ray	mrt_create_ray(t_vec4 origin, t_vec4 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	mrt_generate_ray(t_camera_view cam, float x, float y, t_window window)
{
	float	normalized_x;
	float	normalized_y;
	t_vec4	image_point;
	t_vec4	ray_dir;

	normalized_x = x / (window.width - 1);
	normalized_y = y / (window.height - 1);
	image_point = cam.bottom_left_corner + (normalized_x * cam.horizontal) + \
	(normalized_y * cam.vertical);
	ray_dir = image_point - cam.origin;
	return (mrt_create_ray(cam.origin, ray_dir));
}

void	mrt_draw_to_window(t_window window, t_data *elements)
{
	int				j;
	int				i;
	t_camera_view	camera;
	t_ray			ray;
	t_vec4			color;

	j = 0;
	camera = mrt_compute_camera_view(elements->camera);
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
