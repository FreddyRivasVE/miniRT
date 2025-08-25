/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_light_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:46:37 by brivera           #+#    #+#             */
/*   Updated: 2025/08/25 20:29:23 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	mrt_intersect_scene(t_data *elements, t_ray *ray, t_hit *shadow_hit)
{
	t_scene_node	*current;
	t_hit			temp_hit;
	t_hit			*temp_ptr;
	float			closest_t;
	bool			hit_any;

	current = elements->objects;
	closest_t = INFINITY;
	hit_any = false;
	while (current)
	{
		if (current->type == SPHERE)
		{
			temp_ptr = &temp_hit;
			if (mrt_hit_sphere(ray, *(t_sphere *)current->object, &temp_ptr)
				&& temp_ptr->t > EPSILON && temp_ptr->t < closest_t)
			{
				closest_t = temp_ptr->t;
				*shadow_hit = *temp_ptr;
				hit_any = true;
			}
		}
		if (current->type == PLANE)
		{
			temp_ptr = &temp_hit;
			if (mrt_hit_plane(ray, *(t_plane *)current->object, &temp_ptr)
				&& temp_ptr->t > EPSILON && temp_ptr->t < closest_t)
			{
				closest_t = temp_ptr->t;
				*shadow_hit = *temp_ptr;
				hit_any = true;
			}
		}
		if (current->type == CYLINDER)
		{
			temp_ptr = &temp_hit;
			if (mrt_hit_cylinder(ray, *(t_cylinder *)current->object, &temp_ptr)
				&& temp_ptr->t > EPSILON && temp_ptr->t < closest_t)
			{
				closest_t = temp_ptr->t;
				*shadow_hit = *temp_ptr;
				hit_any = true;
			}
		}
		current = current->next;
	}
	if (hit_any)
		shadow_hit->t = closest_t;
	return (hit_any);
}

t_vec4	mrt_light_color(t_data *elements, t_hit *hit, t_ray *ray)
{
	t_vec4		hit_color;
	t_vec4		view_dir;
	t_vec4		reflect_dir;
	t_ray		shadow_ray;
	t_hit		shadow_hit;


	hit_color = (t_vec4){0, 0, 0, 0};
	shadow_hit.t = INFINITY;
	elements->light->dist = vect4_length(vec4_sub(elements->light->position, hit->point));
	elements->light->dir = vec4_normalize(vec4_sub(elements->light->position, hit->point));
	shadow_ray = mrt_create_ray(vec4_add(hit->point, vec4_scale(hit->normal, E_LIGHT)), elements->light->dir);
	hit->material->ambient = vec4_scale(elements->ambient->color, elements->ambient->ratio);
	if (!mrt_intersect_scene(elements, &shadow_ray, &shadow_hit)
		|| shadow_hit.t >= elements->light->dist - E_LIGHT)
	{
		hit->material->diff_intensity = fmax(0.0f, vec4_dot(hit->normal, elements->light->dir)) * elements->light->brightness_r;
		hit->material->diffuse = vec4_scale(elements->light->color, hit->material->diff_intensity);
		view_dir = vec4_normalize(vec4_sub(ray->origin, hit->point));
		reflect_dir = vec4_reflect(vec4_scale(elements->light->dir, -1.0f), hit->normal);
		hit->material->shininess = 20.0f; //configurar segun material
		hit->material->spec_intensity = powf(fmax(0.0f, vec4_dot(view_dir, reflect_dir)), hit->material->shininess) * elements->light->brightness_r;
		hit->material->specular = vec4_scale(elements->light->color, hit->material->spec_intensity);
		hit_color = vec4_add(hit->material->ambient, vec4_add(hit->material->diffuse, hit->material->specular));
	}
	else
		hit_color = hit->material->ambient;
	return (vec4_mul(hit_color, hit->material->base_color));
}
