/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_light_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:46:37 by brivera           #+#    #+#             */
/*   Updated: 2025/08/27 14:05:10 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	mrt_light_color(t_data *elements, t_hit *hit, t_ray *ray)
{
	t_vec4		hit_color;
	t_vec4		view_dir;
	t_vec4		reflect_dir;
	t_ray		shadow_ray;
	t_hit		shadow_hit;

	hit_color = (t_vec4){0, 0, 0, 0};
	shadow_hit.t = INFINITY;
	elements->light->dist = vect4_length(vec4_sub(elements->light->position,
				hit->point));
	elements->light->dir = vec4_normalize(vec4_sub(elements->light->position,
				hit->point));
	shadow_ray = mrt_create_ray(vec4_add(hit->point, vec4_scale(hit->normal,
					E_LIGHT)), elements->light->dir);
	hit->material->ambient = vec4_scale(elements->ambient->color,
			elements->ambient->ratio);
	if (!mrt_intersect_scene(elements, &shadow_ray, &shadow_hit)
		|| shadow_hit.t >= elements->light->dist - E_LIGHT)
	{
		hit->material->diff_intensity = fmax(0.0f, vec4_dot(hit->normal,
					elements->light->dir)) * elements->light->brightness_r;
		hit->material->diffuse = vec4_scale(elements->light->color,
				hit->material->diff_intensity);
		view_dir = vec4_normalize(vec4_sub(ray->origin, hit->point));
		reflect_dir = vec4_reflect(vec4_scale(elements->light->dir, -1.0f),
				hit->normal);
		hit->material->shininess = 20.0f; //configurar segun material
		hit->material->spec_intensity = powf(fmax(0.0f, vec4_dot(view_dir,
						reflect_dir)), hit->material->shininess)
			* elements->light->brightness_r;
		hit->material->specular = vec4_scale(elements->light->color,
				hit->material->spec_intensity);
		hit_color = vec4_add(hit->material->ambient,
				vec4_add(hit->material->diffuse, hit->material->specular));
	}
	else
		hit_color = hit->material->ambient;
	return (vec4_mul(hit_color, hit->material->base_color));
}

/**
 * Calcula el vector reflejado de un vector incidente respecto
 * a una normal.
 * Ambos vectores se normalizan antes de calcular la reflexión
 * para asegurar
 * que el resultado sea correcto.
 *
 * @param v Vector incidente (t_vec4)
 * @param n Vector normal de la superficie (t_vec4)
 * @return Vector reflejado (t_vec4)
 */
t_vec4	vec4_reflect(t_vec4 v, t_vec4 n)
{
	t_vec4	v_norm;
	t_vec4	n_norm;
	float	dot;
	t_vec4	scaled_normal;
	t_vec4	reflected;

	v_norm = vec4_normalize(v);
	n_norm = vec4_normalize(n);
	dot = vec4_dot(v_norm, n_norm);
	scaled_normal = vec4_scale(n_norm, 2.0f * dot);
	reflected = vec4_sub(v_norm, scaled_normal);
	return (reflected);
}
