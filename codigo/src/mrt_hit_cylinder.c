/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:18:43 by brivera           #+#    #+#             */
/*   Updated: 2025/08/25 21:00:15 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	mrt_calculate_cylinder_vectors(t_ray *ray, t_cylinder cylinder,t_vec4 *direction, t_vec4 *delta_p_perp)
{
	t_vec4	delta_p;

	*direction = vec4_sub(ray->direction,
			vec4_scale(cylinder.axis,
				vec4_dot(ray->direction, cylinder.axis)));
	delta_p = vec4_sub(ray->origin, cylinder.center);
	*delta_p_perp = vec4_sub(delta_p,
			vec4_scale(cylinder.axis,
				vec4_dot(delta_p, cylinder.axis)));
}

static bool	mrt_get_valid_t(float a, float b, float sqrt_disc, float *t_body)
{
	float	t[2];
	float	tmp;

	t[0] = (-b - sqrt_disc) / (2.0f * a);
	t[1] = (-b + sqrt_disc) / (2.0f * a);
	if (t[0] > t[1])
	{
		tmp = t[0];
		t[0] = t[1];
		t[1] = tmp;
	}
	if (t[0] > 0)
		*t_body = t[0];
	else if (t[1] > 0)
		*t_body = t[1];
	else
		return (false);
	return (true);
}

static bool	mrt_solve_quadratic_cylinder(t_vec4 direction, t_vec4 delta_p_perp, float radius, float *t_body)
{
	float	abc[3];
	float	discrim;
	float	sqrt_disc;

	abc[0] = vec4_dot(direction, direction);
	if (abc[0] < EPSILON)
		return (false);
	abc[1] = 2.0f * vec4_dot(direction, delta_p_perp);
	abc[2] = vec4_dot(delta_p_perp, delta_p_perp) - (radius * radius);
	discrim = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discrim < 0)
		return (false);
	sqrt_disc = sqrt(discrim);
	return (mrt_get_valid_t(abc[0], abc[1], sqrt_disc, t_body));
}

static bool	mrt_check_cylinder_height(t_ray *ray, t_cylinder cylinder, float t_body, t_vec4 *normal_body)
{
	t_vec4	p;
	float	proj;

	p = vec4_add(ray->origin, vec4_scale(ray->direction, t_body));
	proj = vec4_dot(vec4_sub(p, cylinder.center), cylinder.axis);
	if (proj < -cylinder.height / 2.0f - EPSILON
		|| proj > cylinder.height / 2.0f + EPSILON)
		return (false);
	*normal_body = vec4_normalize(
			vec4_sub(p, vec4_add(cylinder.center,
					vec4_scale(cylinder.axis, proj))));
	return (true);
}

static bool	mrt_hit_cylinder_body(t_ray *ray, t_cylinder cylinder, float *t_body, t_vec4 *normal_body)
{
	t_vec4	direction;
	t_vec4	delta_p_perp;

	*t_body = INFINITY;
	*normal_body = (t_vec4){0, 0, 0, 0};
	mrt_calculate_cylinder_vectors(ray, cylinder, &direction, &delta_p_perp);
	if (!mrt_solve_quadratic_cylinder(direction, delta_p_perp,
			cylinder.radius, t_body))
		return (false);
	return (mrt_check_cylinder_height(ray, cylinder, *t_body, normal_body));
}

static t_vec4	mrt_get_cap_center_and_normal(t_cylinder cylinder, bool top, t_vec4 *normal)
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

static bool	mrt_intersect_cap_plane(t_ray *ray, t_vec4 cap_center, t_vec4 normal, float *t)
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

static bool	mrt_hit_cylinder_cap(t_ray *ray, t_cylinder cylinder, float *t_cap, t_vec4 *normal_cap, bool top)
{
	t_vec4	cap_center;
	t_vec4	normal;
	t_vec4	point;
	float	t;

	*t_cap = INFINITY;
	*normal_cap = (t_vec4){0, 0, 0, 0};
	cap_center = mrt_get_cap_center_and_normal(cylinder, top, &normal);
	if (!mrt_intersect_cap_plane(ray, cap_center, normal, &t))
		return (false);
	point = vec4_add(ray->origin, vec4_scale(ray->direction, t));
	if (!mrt_point_in_cap(point, cap_center, cylinder.radius))
		return (false);
	*t_cap = t;
	*normal_cap = normal;
	return (true);
}

static void	mrt_find_closest_hit(t_cylinder_hits hits, float *t_final, t_vec4 *normal_final)
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
	hits.hit_cap_base = mrt_hit_cylinder_cap(ray, cylinder,
			&hits.t_cap_base, &hits.normal_cap_base, false);
	hits.hit_cap_top = mrt_hit_cylinder_cap(ray, cylinder,
			&hits.t_cap_top, &hits.normal_cap_top, true);
	mrt_find_closest_hit(hits, &t_final, &normal_final);
	if (t_final == INFINITY)
		return (false);
	(*hit)->t = t_final;
	(*hit)->point = vec4_add(ray->origin, vec4_scale(ray->direction, t_final));
	(*hit)->normal = normal_final;
	return (true);
}
