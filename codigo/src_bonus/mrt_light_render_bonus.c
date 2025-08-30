/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_light_render_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:46:37 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 19:49:27 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_ray	mrt_create_shadow_ray(t_hit *hit, t_vec4 light_dir)
{
	t_vec4	shadow_origin;

	shadow_origin = vec4_add(hit->point, vec4_scale(hit->normal, E_LIGHT));
	return (mrt_create_ray(shadow_origin, light_dir));
}

static void	mrt_calculate_diffuse(t_light *light, t_hit *hit,
			t_vec4 light_dir)
{
	hit->material->diff_intensity = fmax(0.0f, vec4_dot(hit->normal,
				light_dir)) * light->brightness_r;
	hit->material->diffuse = vec4_scale(light->color,
			hit->material->diff_intensity);
}

static void	mrt_calculate_specular(t_light *light, t_hit *hit, t_ray *ray,
		t_vec4 light_dir)
{
	t_vec4	view_dir;
	t_vec4	reflect_dir;

	view_dir = vec4_normalize(vec4_sub(ray->origin, hit->point));
	reflect_dir = vec4_reflect(vec4_scale(light_dir, -1.0f), hit->normal);
	hit->material->shininess = SHININESS_ACTIVE;
	hit->material->spec_intensity = powf(fmax(0.0f, vec4_dot(view_dir,
					reflect_dir)), hit->material->shininess)
		* light->brightness_r * REFLECTION_INTENSITY;
	hit->material->specular = vec4_scale(light->color,
			hit->material->spec_intensity);
}

t_vec4	mrt_one_light_color(t_data *elements, t_hit *hit, t_ray *ray,
		t_light *light)
{
	t_vec4		light_dir;
	t_vec4		hit_color;
	t_ray		shadow_ray;
	t_hit		shadow_hit;
	float		light_dist;

	hit_color = (t_vec4){0, 0, 0, 0};
	shadow_hit.t = INFINITY;
	mrt_setup_lighting_vectors(light, hit, &light_dir, &light_dist);
	shadow_ray = mrt_create_shadow_ray(hit, light_dir);
	if (!mrt_intersect_scene(elements, &shadow_ray, &shadow_hit)
		|| shadow_hit.t >= light_dist - E_LIGHT)
	{
		mrt_calculate_diffuse(light, hit, light_dir);
		mrt_calculate_specular(light, hit, ray, light_dir);
		hit_color = vec4_add(hit->material->diffuse, hit->material->specular);
	}
	return (hit_color);
}

t_vec4	mrt_light_color(t_data *elements, t_hit *hit, t_ray *ray)
{
	t_vec4		sum;
	t_vec4		contrib;
	t_light		*node;
	t_light		*light;

	sum = (t_vec4){0, 0, 0, 0};
	mrt_set_ambient(elements, hit, &sum);
	node = elements->light;
	while (node)
	{
		light = (t_light *)node;
		contrib = mrt_one_light_color(elements, hit, ray, light);
		sum = vec4_add(sum, contrib);
		node = node->next;
	}
	return (vec4_mul(sum, hit->material->base_color));
}
