/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_light_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:46:37 by brivera           #+#    #+#             */
/*   Updated: 2025/08/28 16:13:40 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	mrt_setup_lighting_vectors(t_data *elements, t_hit *hit)
{
	elements->light->dist = vect4_length(vec4_sub(elements->light->position,
				hit->point));
	elements->light->dir = vec4_normalize(vec4_sub(elements->light->position,
				hit->point));
	hit->material->ambient = vec4_scale(elements->ambient->color,
			elements->ambient->ratio);
}

static t_ray	mrt_create_shadow_ray(t_hit *hit, t_vec4 light_dir)
{
	t_vec4	shadow_origin;

	shadow_origin = vec4_add(hit->point, vec4_scale(hit->normal, E_LIGHT));
	return (mrt_create_ray(shadow_origin, light_dir));
}

static void	mrt_calculate_diffuse(t_data *elements, t_hit *hit)
{
	hit->material->diff_intensity = fmax(0.0f, vec4_dot(hit->normal,
				elements->light->dir)) * elements->light->brightness_r;
	hit->material->diffuse = vec4_scale(elements->light->color,
			hit->material->diff_intensity);
}

static void	mrt_calculate_specular(t_data *elements, t_hit *hit, t_ray *ray)
{
	t_vec4	view_dir;
	t_vec4	reflect_dir;

	view_dir = vec4_normalize(vec4_sub(ray->origin, hit->point));
	reflect_dir = vec4_reflect(vec4_scale(elements->light->dir, -1.0f),
			hit->normal);
	hit->material->shininess = SHININESS_ACTIVE;
	hit->material->spec_intensity = powf(fmax(0.0f, vec4_dot(view_dir,
					reflect_dir)), hit->material->shininess)
		* elements->light->brightness_r * REFLECTION_INTENSITY;
	hit->material->specular = vec4_scale(elements->light->color,
			hit->material->spec_intensity);
}

t_vec4	mrt_light_color(t_data *elements, t_hit *hit, t_ray *ray)
{
	t_vec4		hit_color;
	t_ray		shadow_ray;
	t_hit		shadow_hit;

	hit_color = (t_vec4){0, 0, 0, 0};
	shadow_hit.t = INFINITY;
	mrt_setup_lighting_vectors(elements, hit);
	shadow_ray = mrt_create_shadow_ray(hit, elements->light->dir);
	if (!mrt_intersect_scene(elements, &shadow_ray, &shadow_hit)
		|| shadow_hit.t >= elements->light->dist - E_LIGHT)
	{
		mrt_calculate_diffuse(elements, hit);
		mrt_calculate_specular(elements, hit, ray);
		hit_color = vec4_add(hit->material->ambient,
				vec4_add(hit->material->diffuse, hit->material->specular));
	}
	else
		hit_color = hit->material->ambient;
	return (vec4_mul(hit_color, hit->material->base_color));
}
