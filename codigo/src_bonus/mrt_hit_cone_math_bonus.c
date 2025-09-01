/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cone_math_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 18:00:00 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 18:29:01 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

float	mrt_calc_cone_slope_factors(t_cone cone, float *sin_alpha)
{
	float	hypotenuse;
	float	cos_alpha;

	hypotenuse = sqrtf(cone.height * cone.height + cone.radius * cone.radius);
	cos_alpha = cone.height / hypotenuse;
	*sin_alpha = cone.radius / hypotenuse;
	return (cos_alpha);
}

t_vec4	mrt_cone_normal_at_point(t_cone cone, t_vec4 point)
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

void	mrt_calc_cone_coefficients(t_ray *ray, t_cone cone, float *abc)
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

bool	mrt_hit_infinite_cone(t_ray *ray, t_cone cone, float *t_out)
{
	float	abc[3];
	float	discriminant;

	mrt_calc_cone_coefficients(ray, cone, abc);
	discriminant = abc[1] * abc[1] - 4.0f * abc[0] * abc[2];
	if (discriminant < 0.0f)
		return (false);
	return (mrt_get_valid_t(abc[0], abc[1], sqrtf(discriminant), t_out));
}
