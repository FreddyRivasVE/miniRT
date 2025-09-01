/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:35:48 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 16:48:18 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static float	mrt_calc_cone_slope_factors(t_cone cone, float *sin_alpha)
{
	float	hypotenuse;
	float	cos_alpha;

	hypotenuse = sqrtf(cone.height * cone.height + cone.radius * cone.radius);
	cos_alpha = cone.height / hypotenuse;
	*sin_alpha = cone.radius / hypotenuse;
	return (cos_alpha);
}

static t_vec4	mrt_cone_normal_at_point(t_cone cone, t_vec4 point)
{
	t_vec4	to_point;
	t_vec4	radial_vector;
	float	cos_alpha;
	float	sin_alpha;
	t_vec4	normal;

	to_point = vec4_sub(point, cone.origin);
	radial_vector = vec4_sub(to_point, vec4_scale(cone.axis,
				vec4_dot(to_point, cone.axis)));
	cos_alpha = mrt_calc_cone_slope_factors(cone, &sin_alpha);
	normal = vec4_sub(vec4_scale(vec4_normalize(radial_vector), cos_alpha),
			vec4_scale(cone.axis, sin_alpha));
	return (vec4_normalize(normal));
}

static void	mrt_calc_cone_coefficients(t_ray *ray, t_cone cone, float *abc)
{
	t_vec4	oc;
	float	cos_squared;
	float	rd_dot_axis;
	float	oc_dot_axis;

	oc = vec4_sub(ray->origin, cone.origin);
	cos_squared = (cone.radius * cone.radius) / (cone.height * cone.height);
	rd_dot_axis = vec4_dot(ray->direction, cone.axis);
	oc_dot_axis = vec4_dot(oc, cone.axis);
	abc[0] = vec4_dot(ray->direction, ray->direction)
		- (1.0f + cos_squared) * (rd_dot_axis * rd_dot_axis);
	abc[1] = 2.0f * (vec4_dot(ray->direction, oc)
			- (1.0f + cos_squared) * rd_dot_axis * oc_dot_axis);
	abc[2] = vec4_dot(oc, oc)
		- (1.0f + cos_squared) * (oc_dot_axis * oc_dot_axis);
}

static bool	mrt_hit_infinite_cone(t_ray *ray, t_cone cone, float *t_out)
{
	float	abc[3];
	float	discriminant;

	mrt_calc_cone_coefficients(ray, cone, abc);
	discriminant = abc[1] * abc[1] - 4.0f * abc[0] * abc[2];
	if (discriminant < 0.0f)
		return (false);
	return (mrt_get_valid_t(abc[0], abc[1], sqrtf(discriminant), t_out));
}

static bool	mrt_intersect_base_plane(t_ray *ray, t_cone cone, float *t)
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

static bool	mrt_point_in_base_circle(t_ray *ray, t_cone cone, float t)
{
	t_vec4	point;
	t_vec4	diff;

	point = vec4_add(ray->origin, vec4_scale(ray->direction, t));
	diff = vec4_sub(point, cone.origin);
	return (vec4_dot(diff, diff) <= cone.radius * cone.radius);
}

static bool	mrt_hit_cone_base(t_ray *ray, t_cone cone, float *t_out)
{
	float	t;

	if (!mrt_intersect_base_plane(ray, cone, &t))
		return (false);
	if (!mrt_point_in_base_circle(ray, cone, t))
		return (false);
	*t_out = t;
	return (true);
}

static t_cone	mrt_create_adjusted_cone(t_cone cone)
{
	t_cone	adjusted_cone;

	adjusted_cone.origin = vec4_add(cone.origin, 
			vec4_scale(cone.axis, cone.height));
	adjusted_cone.axis = vec4_scale(cone.axis, -1.0f);
	adjusted_cone.radius = cone.radius;
	adjusted_cone.height = cone.height;
	return (adjusted_cone);
}

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
