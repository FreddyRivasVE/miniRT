/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cylinder_body_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:28:18 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 13:14:50 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	mrt_calculate_cylinder_vectors(t_ray *ray,
			t_cylinder cylinder, t_vec4 *direction, t_vec4 *delta_p_perp)
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

static bool	mrt_solve_quadratic_cylinder(t_vec4 direction, t_vec4 delta_p_perp,
			float radius, float *t_body)
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

static bool	mrt_check_cylinder_height(t_ray *ray, t_cylinder cylinder,
			float t_body, t_vec4 *normal_body)
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

bool	mrt_hit_cylinder_body(t_ray *ray, t_cylinder cylinder,
			float *t_body, t_vec4 *normal_body)
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
