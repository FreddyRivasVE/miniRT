/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_sphere_and_plane.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:50:01 by brivera           #+#    #+#             */
/*   Updated: 2025/08/21 23:04:08 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	mrt_hit_sphere(t_ray ray, t_sphere sphere, float *t_hit)
{
	t_vec4	ray_to_center;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	ray_to_center = vec4_sub(ray.origin, sphere.center);
	a = vec4_dot(ray.direction, ray.direction);
	b = 2.0f * vec4_dot(ray_to_center, ray.direction);
	c = vec4_dot(ray_to_center, ray_to_center)
		- (sphere.radius * sphere.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	*t_hit = (-b - sqrtf(discriminant)) / (2.0f * a);
	if (*t_hit < 0)
		return (false);
	return (true);
}

bool	mrt_hit_plane(t_ray ray, t_plane plane, float *t_hit)
{
	float	denom;
	float	t;
	t_vec4	to_plane;

	denom = vec4_dot(plane.normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	to_plane = plane.point - ray.origin;
	t = vec4_dot(to_plane, plane.normal) / denom;
	if (t < 0)
		return (false);
	*t_hit = t;
	return (true);
}
