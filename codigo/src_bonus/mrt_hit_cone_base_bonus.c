/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cone_base_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:00:00 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 18:37:49 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

bool	mrt_intersect_base_plane(t_ray *ray, t_cone cone, float *t)
{
	t_vec4	normal;
	float	denom;

	normal = vec4_scale(cone.axis, -1.0f);
	denom = vec4_dot(ray->direction, normal);
	if (fabs(denom) < EPSILON)
		return (false);
	*t = vec4_dot(vec4_sub(cone.origin, ray->origin), normal) / denom;
	return (*t > EPSILON);
}

bool	mrt_point_in_base_circle(t_ray *ray, t_cone cone, float t)
{
	t_vec4	point;
	t_vec4	diff;

	point = vec4_add(ray->origin, vec4_scale(ray->direction, t));
	diff = vec4_sub(point, cone.origin);
	return (vec4_dot(diff, diff) <= cone.radius * cone.radius);
}

bool	mrt_hit_cone_base(t_ray *ray, t_cone cone, float *t_out)
{
	float	t;

	if (!mrt_intersect_base_plane(ray, cone, &t))
		return (false);
	if (!mrt_point_in_base_circle(ray, cone, t))
		return (false);
	*t_out = t;
	return (true);
}

t_cone	mrt_create_adjusted_cone(t_cone cone)
{
	t_cone	adjusted_cone;

	adjusted_cone.origin = vec4_add(cone.origin,
			vec4_scale(cone.axis, cone.height));
	adjusted_cone.axis = vec4_scale(cone.axis, -1.0f);
	adjusted_cone.radius = cone.radius;
	adjusted_cone.height = cone.height;
	return (adjusted_cone);
}
