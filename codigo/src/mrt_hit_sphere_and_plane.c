/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_sphere_and_plane.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:50:01 by brivera           #+#    #+#             */
/*   Updated: 2025/08/24 10:38:21 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	mrt_hit_sphere(t_ray *ray, t_sphere sphere, t_hittable **hit)
{
	t_vec4	ray_to_center;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t0;
	float	t1;

	ray_to_center = vec4_sub(ray->origin, sphere.center);
	a = vec4_dot(ray->direction, ray->direction);
	b = 2.0f * vec4_dot(ray_to_center, ray->direction);
	c = vec4_dot(ray_to_center, ray_to_center)
		- (sphere.radius * sphere.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	t0 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t1 = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t0 > EPSILON)
		(*hit)->t = t0;
	else if (t1 > EPSILON)
		(*hit)->t = t1;
	else
		return (false);
	(*hit)->point = vec4_add(ray->origin, vec4_scale(ray->direction, (*hit)->t));
	(*hit)->normal = vec4_normalize(vec4_sub((*hit)->point, sphere.center));
	if (vec4_dot(ray->direction, (*hit)->normal) > 0)
		(*hit)->normal = vec4_scale((*hit)->normal, -1);
	return (true);
}

bool	mrt_hit_plane(t_ray ray, t_plane plane, t_hittable **hit)
{
	t_vec4	to_plane;
	float	denom;

	denom = vec4_dot(plane.normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	to_plane = vec4_sub(plane.point, ray.origin);
	(*hit)->t = vec4_dot(to_plane, plane.normal) / denom;
	if ((*hit)->t < 0)
		return (false);
	(*hit)->point = vec4_add(ray.origin, vec4_scale(ray.direction, (*hit)->t));
	(*hit)->normal = plane.normal;
	if (vec4_dot(ray.direction, (*hit)->normal) > 0)
		(*hit)->normal = vec4_scale((*hit)->normal, -1);
	return (true);
}
