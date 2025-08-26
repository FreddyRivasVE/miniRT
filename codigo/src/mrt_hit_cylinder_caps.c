/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cylinder_caps.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 12:13:13 by frivas            #+#    #+#             */
/*   Updated: 2025/08/26 12:51:26 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec4	mrt_get_cap_center_and_normal(t_cylinder cylinder, bool top,
				t_vec4 *normal)
{
	t_vec4	cap_center;

	if (top)
		cap_center = vec4_add(cylinder.center, vec4_scale(cylinder.axis,
					cylinder.height / 2.0f));
	else
		cap_center = vec4_sub(cylinder.center, vec4_scale(cylinder.axis,
					cylinder.height / 2.0f));
	*normal = vec4_normalize(cylinder.axis);
	if (!top)
		*normal = vec4_scale(*normal, -1.0f);
	return (cap_center);
}

static bool	mrt_intersect_cap_plane(t_ray *ray, t_vec4 cap_center,
			t_vec4 normal, float *t)
{
	float	denom;

	denom = vec4_dot(ray->direction, normal);
	if (fabs(denom) < EPSILON)
		return (false);
	*t = vec4_dot(vec4_sub(cap_center, ray->origin), normal) / denom;
	return (*t >= 0);
}

static bool	mrt_point_in_cap(t_vec4 point, t_vec4 cap_center, float radius)
{
	t_vec4	diff;
	float	dist_squared;

	diff = vec4_sub(point, cap_center);
	dist_squared = vec4_dot(diff, diff);
	return (dist_squared <= radius * radius);
}

void	mrt_check_flag(float *t_cap, t_vec4 *normal_cap, float t, t_vec4 normal)
{
	*t_cap = t;
	*normal_cap = normal;
}

bool	mrt_hit_cylinder_cap(t_ray *ray, t_cylinder cylinder,
		t_cylinder_hits *hits, bool top)
{
	t_vec4	cap_center;
	t_vec4	normal;
	t_vec4	point;
	float	t;

	if (top)
		mrt_check_flag(&hits->t_cap_top, &hits->normal_cap_top, INFINITY,
			(t_vec4){0, 0, 0, 0});
	else
		mrt_check_flag(&hits->t_cap_base, &hits->normal_cap_base, INFINITY,
			(t_vec4){0, 0, 0, 0});
	cap_center = mrt_get_cap_center_and_normal(cylinder, top, &normal);
	if (!mrt_intersect_cap_plane(ray, cap_center, normal, &t))
		return (false);
	point = vec4_add(ray->origin, vec4_scale(ray->direction, t));
	if (!mrt_point_in_cap(point, cap_center, cylinder.radius))
		return (false);
	if (top)
		mrt_check_flag(&hits->t_cap_top, &hits->normal_cap_top, t, normal);
	else
		mrt_check_flag(&hits->t_cap_base, &hits->normal_cap_base, t, normal);
	return (true);
}
