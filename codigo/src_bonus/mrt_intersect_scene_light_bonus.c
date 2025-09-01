/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_intersect_scene_light_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:04:51 by frivas            #+#    #+#             */
/*   Updated: 2025/09/01 18:40:05 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

static bool	mrt_hit_cone_light(t_ray *ray, t_scene_node *object, float *t,
		t_hit *hit)
{
	t_hit	*temp_ptr;
	t_hit	temp_hit;

	if (object->type == CONE)
	{
		temp_ptr = &temp_hit;
		if (mrt_hit_cone(ray, *(t_cone *)object->object, &temp_ptr)
			&& temp_ptr->t > EPSILON && temp_ptr->t < *t)
		{
			*t = temp_ptr->t;
			*hit = *temp_ptr;
			return (true);
		}
	}
	return (false);
}

bool	mrt_object_hit_light(t_scene_node *current, float *t,
		t_hit *shadow_hit, t_ray *ray)
{
	if (mrt_hit_sp_light(ray, current, t, shadow_hit))
		return (true);
	if (mrt_hit_pl_light(ray, current, t, shadow_hit))
		return (true);
	if (mrt_hit_cy_light(ray, current, t, shadow_hit))
		return (true);
	if (mrt_hit_cone_light(ray, current, t, shadow_hit))
		return (true);
	return (false);
}
