/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:35:48 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 18:28:57 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static bool	mrt_check_cone_surface_hit(t_ray *ray, t_cone adjusted_cone,
	float *t_cone_surface, float t_final)
{
	t_vec4	point;
	float	height_check;

	if (!mrt_hit_infinite_cone(ray, adjusted_cone, t_cone_surface))
		return (false);
	if (*t_cone_surface <= EPSILON || *t_cone_surface >= t_final)
		return (false);
	point = vec4_add(ray->origin, vec4_scale(ray->direction, *t_cone_surface));
	height_check = vec4_dot(vec4_sub(point, adjusted_cone.origin),
			adjusted_cone.axis);
	if (height_check >= 0.0f && height_check <= adjusted_cone.height)
		return (true);
	return (false);
}

static void	mrt_set_cone_hit_data(t_cone_hit_data data, t_cone cone,
	t_cone adjusted_cone)
{
	(*data.hit)->t = data.t_final;
	(*data.hit)->point = vec4_add(data.ray->origin,
			vec4_scale(data.ray->direction, data.t_final));
	if (data.is_base_hit)
		(*data.hit)->normal = vec4_scale(cone.axis, -1.0f);
	else
		(*data.hit)->normal = mrt_cone_normal_at_point(adjusted_cone,
				(*data.hit)->point);
}

static t_cone_hit_data	mrt_process_cone_intersections(t_ray *ray,
	t_cone cone, t_cone adjusted_cone)
{
	t_cone_hit_data	result;
	float			t_cone_surface;
	float			t_base;

	result.t_final = INFINITY;
	result.is_base_hit = false;
	result.has_intersection = false;
	if (mrt_hit_cone_base(ray, cone, &t_base) && t_base > EPSILON)
	{
		result.t_final = t_base;
		result.is_base_hit = true;
		result.has_intersection = true;
	}
	if (mrt_check_cone_surface_hit(ray, adjusted_cone, &t_cone_surface,
			result.t_final))
	{
		result.t_final = t_cone_surface;
		result.is_base_hit = false;
		result.has_intersection = true;
	}
	return (result);
}

bool	mrt_hit_cone(t_ray *ray, t_cone cone, t_hit **hit)
{
	t_cone			adjusted_cone;
	t_cone_hit_data	intersection;

	adjusted_cone = mrt_create_adjusted_cone(cone);
	intersection = mrt_process_cone_intersections(ray, cone, adjusted_cone);
	if (!intersection.has_intersection)
		return (false);
	intersection.ray = ray;
	intersection.hit = hit;
	mrt_set_cone_hit_data(intersection, cone, adjusted_cone);
	return (true);
}
