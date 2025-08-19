/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_create_render_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:17:04 by brivera           #+#    #+#             */
/*   Updated: 2025/08/19 14:06:57 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	mrt_hit_sphere(t_ray ray, t_sphere sphere, float *t_hit)
{
	t_vec4	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = ray.origin - sphere.center;
	a = vec4_dot(ray.direction, ray.direction);
	b = 2.0f * vec4_dot(oc, ray.direction);
	c = vec4_dot(oc, oc) - (sphere.radius * sphere.radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	*t_hit = (-b - sqrtf(discriminant)) / (2.0f * a);
	return (*t_hit > 0);
}

bool	mrt_hit_plane(t_ray ray, t_plane plane, float *t_hit)
{
	float	denom;
	float	t;
	t_vec4	to_plane;

	denom = vec4_dot(plane.normal, ray.direction);
	if (fabs(denom) < 1e-6) // casi 0, el rayo es paralelo
		return (false);
	to_plane = plane.point - ray.origin;
	t = vec4_dot(to_plane, plane.normal) / denom;
	if (t < 0)
		return (false); // intersección detrás del origen
	*t_hit = t;
	return (true);
}

bool	mrt_hit_cylinder_body(t_ray ray, t_cylinder cylinder, float *t)
{
	bool	hit;
	float	t_hit;
	t_vec4	direction;
	t_vec4	delta_p;
	t_vec4	delta_p_perp;
	t_vec4	p;
	float	a;
	float	b;
	float	c;
	float	discrim;
	float	sqrt_disc;
	float	t0;
	float	t1;
	float	proj;
	
	t_hit = INFINITY;
	direction = vec4_sub(ray.direction, vec4_scale(cylinder.axis,
				vec4_dot(ray.direction, cylinder.axis)));
	delta_p = vec4_sub(ray.origin, cylinder.center);
	delta_p_perp = vec4_sub(delta_p, vec4_scale(cylinder.axis,
				vec4_dot(delta_p, cylinder.axis)));
	a = vec4_dot(direction, direction);
	b = 2.0f * vec4_dot(direction, delta_p_perp);
	c = vec4_dot(delta_p_perp, delta_p_perp) - cylinder.radius
		* cylinder.radius;
	discrim = b * b - 4 * a * c;
	if (discrim < 0)
		return (false);
	sqrt_disc = sqrt(discrim);
	t0 = (-b - sqrt_disc) / (2.0f * a);
	t1 = (-b + sqrt_disc) / (2.0f * a);
	if (t0 > 0)
		*t = t0;
	else
		*t = t1;
	if (*t < 0)
		return (false);
	p = vec4_add(ray.origin, vec4_scale(ray.direction, *t));
	proj = vec4_dot(vec4_sub(p, cylinder.center), cylinder.axis);
	if (proj < 0.0f || proj > cylinder.height)
		return (false);
	cylinder.normal = vec4_normalize(vec4_sub(p, vec4_add(cylinder.center,
					vec4_scale(cylinder.axis, proj))));
	return (true);
}

bool	mrt_hit_cylinder(t_ray ray, t_cylinder cylinder, float *t_hit)
{
	bool	hit;
	float	t1;

	hit = mrt_hit_cylinder_body(ray, cylinder, &t1);
}
