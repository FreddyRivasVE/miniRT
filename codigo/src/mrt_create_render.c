/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_create_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:03:36 by brivera           #+#    #+#             */
/*   Updated: 2025/08/14 10:39:50 by frivas           ###   ########.fr       */
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

/* t_vec4 mrt_ray_color(t_ray ray, t_data *elements)
{
	t_scene_node	*current;
	t_vec4			final_color;
	float			closest_t;
	t_sphere		*hit_sphere;
	t_vec4			hit_color;
	float			t;

	final_color = vec4_create(0, 0, 0, 0);
	closest_t = INFINITY;
	hit_sphere = NULL;
		current = elements->objects;
	while (current)
	{
		if (current->type == SPHERE)
		{
			if (mrt_hit_sphere(ray, *(t_sphere *)current->object, &t) && 
				t < closest_t && t > 0.001f)
			{
				closest_t = t;
				hit_sphere = (t_sphere *)current->object;
				hit_color = current->color;
			}
		}
		current = current->next;
	}
	if (!hit_sphere)
		return (vec4_create(0, 0, 0, 0));
	// Cálculos de iluminación
	t_vec4 hit_point = vec4_add(ray.origin, vec4_scale(ray.direction, closest_t));
	t_vec4 normal = vec4_normalize(vec4_sub(hit_point, hit_sphere->center));
	// Asegurar que la normal apunte hacia el rayo
	if (vec4_dot(normal, ray.direction) > 0.0f)
		normal = vec4_scale(normal, -1.0f);
	// Componente ambiental
	t_vec4 ambient = vec4_scale(elements->ambient->color, elements->ambient->ratio);
	// Componente difusa
	t_vec4 light_dir = vec4_normalize(vec4_sub(elements->light->position, hit_point));
	float diff_intensity = fmaxf(0.0f, vec4_dot(normal, light_dir));
	t_vec4 diffuse = vec4_scale(vec4_mul(hit_color, elements->light->diff_color), 
			diff_intensity * elements->light->diff_power);
	// Componente especular
	t_vec4 view_dir = vec4_normalize(vec4_sub(ray.origin, hit_point));
	t_vec4 reflect_dir = vec4_reflect(vec4_scale(light_dir, -1.0f), normal);
	float spec_intensity = powf(fmaxf(0.0f, vec4_dot(view_dir, reflect_dir)), 
			32.0f) * elements->light->spec_power;
	t_vec4 specular = vec4_scale(elements->light->spec_color, spec_intensity);
	// Combinar componentes
	final_color = vec4_add(ambient, vec4_add(diffuse, specular));
	final_color = vec4_mul(final_color, hit_color);
	return (vec4_clamp(final_color, 0.0f, 1.0f));
} */

t_vec4 mrt_ray_color(t_ray ray, t_data *elements) // para ver sin luces 
{
	t_scene_node    *current;
	float           closest_t;
	t_sphere        *hit_sphere;
	t_vec4          hit_color;
	float           t;

	// Inicialización de variables
	closest_t = INFINITY;
	hit_sphere = NULL;
	current = elements->objects;

	// Buscar intersección más cercana
	while (current)
	{
		if (current->type == SPHERE)
		{
			if (mrt_hit_sphere(ray, *(t_sphere *)current->object, &t) && 
				t < closest_t && t > 0.001f)
			{
				closest_t = t;
				hit_sphere = (t_sphere *)current->object;
				hit_color = current->color;
			}
		}
		current = current->next;
	}

	// Si no hay intersección, fondo negro
	if (!hit_sphere)
		return (vec4_create(0, 0, 0, 0));

	// Solo devolver el color base de la esfera (sin iluminación)
	return hit_color;
}

t_ray	mrt_create_ray(t_vec4 origin, t_vec4 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

/*t_ray mrt_generate_ray(t_camera_view cam, float x, float y, t_window window)
{
	float		u;
	float		v;
	t_vec4		direction;
	t_vec4		horizontal_offset;
	t_vec4		vertical_offset;

	u = x / (float)(window.width - 1);
	v = 1.0f - (y / (float)(window.height - 1)); 
	horizontal_offset = vec4_scale(cam.horizontal, u);
	vertical_offset = vec4_scale(cam.vertical, v);
	direction = vec4_add(cam.bottom_left_corner, 
						vec4_add(horizontal_offset, vertical_offset));
	direction = vec4_normalize(vec4_sub(direction, cam.origin));
	return (mrt_create_ray(cam.origin, direction));
}*/

t_ray mrt_generate_ray(t_camera_view cam, float x, float y, t_window window)
{
    float u = (x + 0.5f) / (float)window.width;   // coordenada horizontal normalizada [0,1]
    float v = (y + 0.5f) / (float)window.height;  // coordenada vertical normalizada [0,1]

    // Importante: invertir v si el sistema de coordenadas de la imagen tiene el (0,0) arriba
    v = 1.0f - v;

    // Punto en el plano de proyección
    t_vec4 point_on_plane = cam.bottom_left_corner;
    point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.horizontal, u));
    point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.vertical, v));

    // Dirección normalizada desde el origen de la cámara hacia ese punto
    t_vec4 direction = vec4_normalize(vec4_sub(point_on_plane, cam.origin));

    return mrt_create_ray(cam.origin, direction);
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
