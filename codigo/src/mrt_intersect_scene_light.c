/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_intersect_scene_light.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:04:51 by frivas            #+#    #+#             */
/*   Updated: 2025/08/27 14:05:16 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	mrt_hit_cy_light(t_ray *ray, t_scene_node *object, float *t,
		t_hit *hit)
{
	t_hit	*temp_ptr;
	t_hit	temp_hit;

	if (object->type == CYLINDER)
	{
		temp_ptr = &temp_hit;
		if (mrt_hit_cylinder(ray, *(t_cylinder *)object->object, &temp_ptr)
			&& temp_ptr->t > EPSILON && temp_ptr->t < *t)
		{
			*t = temp_ptr->t;
			*hit = *temp_ptr;
			return (true);
		}
	}
	return (false);
}

static bool	mrt_hit_pl_light(t_ray *ray, t_scene_node *object, float *t,
		t_hit *hit)
{
	t_hit	*temp_ptr;
	t_hit	temp_hit;

	if (object->type == PLANE)
	{
		temp_ptr = &temp_hit;
		if (mrt_hit_plane(ray, *(t_plane *)object->object, &temp_ptr)
			&& temp_ptr->t > EPSILON && temp_ptr->t < *t)
		{
			*t = temp_ptr->t;
			*hit = *temp_ptr;
			return (true);
		}
	}
	return (false);
}

static bool	mrt_hit_sp_light(t_ray *ray, t_scene_node *object, float *t,
		t_hit *hit)
{
	t_hit	*temp_ptr;
	t_hit	temp_hit;

	if (object->type == SPHERE)
	{
		temp_ptr = &temp_hit;
		if (mrt_hit_sphere(ray, *(t_sphere *)object->object, &temp_ptr)
			&& temp_ptr->t > EPSILON && temp_ptr->t < *t)
		{
			*t = temp_ptr->t;
			*hit = *temp_ptr;
			return (true);
		}
	}
	return (false);
}

static bool	mrt_object_hit_light(t_scene_node *current, float *t,
		t_hit *shadow_hit, t_ray *ray)
{
	if (mrt_hit_sp_light(ray, current, t, shadow_hit))
		return (true);
	if (mrt_hit_pl_light(ray, current, t, shadow_hit))
		return (true);
	if (mrt_hit_cy_light(ray, current, t, shadow_hit))
		return (true);
	return (false);
}

bool	mrt_intersect_scene(t_data *elements, t_ray *ray, t_hit *shadow_hit)
{
	t_scene_node	*current;
	float			closest_t;
	bool			hit_any;

	current = elements->objects;
	closest_t = INFINITY;
	hit_any = false;
	while (current)
	{
		if (mrt_object_hit_light(current, &closest_t, shadow_hit, ray))
			hit_any = true;
		current = current->next;
	}
	if (hit_any)
		shadow_hit->t = closest_t;
	return (hit_any);
}
