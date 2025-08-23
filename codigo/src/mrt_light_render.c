/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_light_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 12:46:37 by brivera           #+#    #+#             */
/*   Updated: 2025/08/23 20:51:08 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	mrt_intersect_scene(t_data *elements, t_ray *ray, t_hittable *shadow_hit)
{
	t_scene_node	*current;
	t_hittable		temp_hit;
	t_hittable		*temp_ptr;
	float			closest_t;
	bool			hit_any;

	current = elements->objects;
	closest_t = INFINITY;
	hit_any = false;
	shadow_hit->t = INFINITY;
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
			}
		}
		// TODO: PLANE / CYLINDER 
		current = current->next;
	}
	return (hit_any);
}

/*
bool	mrt_intersect_scene(t_data *elements, t_ray *ray, t_hittable **shadow_hit)
{
	t_scene_node	*current;
	t_hittable		*temp_hit;
	float			closest_t;
	bool			hit_any;

	hit_any = false;
	closest_t = INFINITY;
	current = elements->objects;
	while (current)
	{
		if (current->type == SPHERE)
		{
			if (mrt_hit_sphere(ray, *(t_sphere *)current->object, &temp_hit)
				&& temp_hit->t < closest_t && temp_hit->t > EPSILON)
			{
				closest_t = temp_hit->t;
				*shadow_hit = temp_hit;
				hit_any = true;
			}
		}
		// if (current->type == PLANE)
		// {
		// 	if (mrt_hit_plane(ray, *(t_plane *)current->object, &current->hit)
		// 		&& current->hit->t < closest_t && current->hit->t > EPSILON)
		// 	{
		// 		return (true);
		// 	}
		// }
		// if (current->type == CYLINDER)
		// {
		// 	if (mrt_hit_cylinder(ray, *(t_cylinder *)current->object, &current->hit)
		// 		&& current->hit->t < closest_t && current->hit->t > 0.001f)
		// 		return (true);
		// }
		current = current->next;
	}
	// if (hit_any)
	// 	(*shadow_hit)->t = closest_t;
	// free(temp_hit); 
	return (hit_any);
}*/

float	vect4_length(t_vec4 v)
{
	float	r;

	r = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return (r);
}

t_vec4  mrt_light_color(t_data *elements, t_hittable *hit, t_ray *ray)
{
	t_vec4  hit_color;
	t_vec4  light_dir;
	t_vec4  diff;
	t_vec4  view_dir;
	t_vec4  reflect_dir;
	t_vec4  spec;
	t_vec4	ambient;
	t_ray	shadow_ray;
	t_hittable shadow_hit;
	float   diff_intensity;
	float   spec_intensity;
	float   shininess;
	float	light_dist;

	//shadow_hit = ft_calloc(1, sizeof(t_hittable));
	light_dist = vect4_length(vec4_sub(elements->light->position, hit->point));
	light_dir = vec4_normalize(vec4_sub(elements->light->position, hit->point));
	shadow_ray.direction = light_dir;
	shadow_ray.origin = vec4_add(hit->point, vec4_scale(hit->normal, 1e-4f));
	ambient = vec4_scale(elements->ambient->color, elements->ambient->ratio);
	//ver si puede poner el init_scene
	diff = (t_vec4){0, 0, 0, 0};
	spec = (t_vec4){0, 0, 0, 0};
	hit_color = (t_vec4){0, 0, 0, 0};
	shadow_hit.t = INFINITY;
	if (!mrt_intersect_scene(elements, &shadow_ray, &shadow_hit) || shadow_hit.t >= light_dist - 1e-4f)
	{
		diff_intensity = fmax(0.0f, vec4_dot(hit->normal, light_dir)) * elements->light->brightness_r;
		diff = vec4_scale(elements->light->color, diff_intensity);
		view_dir = vec4_normalize(vec4_sub(ray->origin, hit->point));
		reflect_dir = vec4_reflect(vec4_scale(light_dir, -1.0f), hit->normal);
		shininess = 20.0f; //configurar segun material
		spec_intensity = powf(fmax(0.0f, vec4_dot(view_dir, reflect_dir)), shininess) * elements->light->brightness_r;
		spec = vec4_scale(elements->light->color, spec_intensity);
		hit_color = vec4_add(ambient, vec4_add(diff, spec));
	}
	else
		hit_color = ambient;
	return (vec4_mul(hit_color, hit->material->base_color));
}
