/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_sphere_and_plane.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:50:01 by brivera           #+#    #+#             */
/*   Updated: 2025/08/26 13:16:37 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	mrt_hit_sphere_intersection(t_ray *ray, t_sphere sphere, float *t)
{
	t_vec4	ray_to_center;
	float	abc[3];
	float	discriminant;
	float	t0;
	float	t1;

	ray_to_center = vec4_sub(ray->origin, sphere.center);
	abc[0] = vec4_dot(ray->direction, ray->direction);
	abc[1] = 2.0f * vec4_dot(ray_to_center, ray->direction);
	abc[2] = vec4_dot(ray_to_center, ray_to_center)
		- (sphere.radius * sphere.radius);
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0)
		return (false);
	t0 = (-abc[1] - sqrtf(discriminant)) / (2.0f * abc[0]);
	t1 = (-abc[1] + sqrtf(discriminant)) / (2.0f * abc[0]);
	if (t0 > EPSILON)
		*t = t0;
	else if (t1 > EPSILON)
		*t = t1;
	else
		return (false);
	return (true);
}

bool	mrt_hit_sphere(t_ray *ray, t_sphere sphere, t_hit **hit)
{
	float	t;

	if (!mrt_hit_sphere_intersection(ray, sphere, &t))
		return (false);
	(*hit)->t = t;
	(*hit)->point = vec4_add(ray->origin,
			vec4_scale(ray->direction, (*hit)->t));
	(*hit)->normal = vec4_normalize(vec4_sub((*hit)->point, sphere.center));
	if (vec4_dot(ray->direction, (*hit)->normal) > 0)
		(*hit)->normal = vec4_scale((*hit)->normal, -1);
	return (true);
}

bool	mrt_hit_plane(t_ray *ray, t_plane plane, t_hit **hit)
{
	t_vec4	to_plane;
	float	denom;

	denom = vec4_dot(plane.normal, ray->direction);
	if (fabs(denom) < EPSILON)
		return (false);
	to_plane = vec4_sub(plane.point, ray->origin);
	(*hit)->t = vec4_dot(to_plane, plane.normal) / denom;
	if ((*hit)->t < 0)
		return (false);
	(*hit)->point = vec4_add(ray->origin, vec4_scale(ray->direction,
				(*hit)->t));
	(*hit)->normal = plane.normal;
	if (vec4_dot(ray->direction, (*hit)->normal) > 0)
		(*hit)->normal = vec4_scale((*hit)->normal, -1);
	return (true);
}

static void	mrt_find_closest_hit(t_cylinder_hits hits, float *t_final,
			t_vec4 *normal_final)
{
	*t_final = INFINITY;
	*normal_final = (t_vec4){0, 0, 0, 0};
	if (hits.hit_body && hits.t_body < *t_final)
	{
		*t_final = hits.t_body;
		*normal_final = hits.normal_body;
	}
	if (hits.hit_cap_base && hits.t_cap_base < *t_final)
	{
		*t_final = hits.t_cap_base;
		*normal_final = hits.normal_cap_base;
	}
	if (hits.hit_cap_top && hits.t_cap_top < *t_final)
	{
		*t_final = hits.t_cap_top;
		*normal_final = hits.normal_cap_top;
	}
}

bool	mrt_hit_cylinder(t_ray *ray, t_cylinder cylinder, t_hit **hit)
{
	t_cylinder_hits	hits;
	t_vec4			normal_final;
	float			t_final;

	hits.hit_body = mrt_hit_cylinder_body(ray, cylinder,
			&hits.t_body, &hits.normal_body);
	hits.hit_cap_base = mrt_hit_cylinder_cap(ray, cylinder, &hits, false);
	hits.hit_cap_top = mrt_hit_cylinder_cap(ray, cylinder, &hits, true);
	mrt_find_closest_hit(hits, &t_final, &normal_final);
	if (t_final == INFINITY)
		return (false);
	(*hit)->t = t_final;
	(*hit)->point = vec4_add(ray->origin, vec4_scale(ray->direction, t_final));
	(*hit)->normal = normal_final;
	return (true);
}
