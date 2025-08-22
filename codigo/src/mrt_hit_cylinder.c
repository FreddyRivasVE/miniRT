/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:18:43 by brivera           #+#    #+#             */
/*   Updated: 2025/08/21 23:06:23 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ----------------------------------
// Intersección con el cuerpo lateral
// ----------------------------------
static bool	mrt_hit_cylinder_body(t_ray ray, t_cylinder cylinder,
	float *t_body, t_vec4 *normal_body)
{
	t_vec4	direction;
	t_vec4	delta_p;
	t_vec4	delta_p_perp;
	float	a;
	float	b;
	float	c;
	float	discrim;
	float	sqrt_disc;
	float	t0;
	float	t1;
	t_vec4	p;
	float	proj;
	float	tmp;

	*t_body = INFINITY;
	*normal_body = (t_vec4){0, 0, 0, 0};
	direction = vec4_sub(ray.direction,
			vec4_scale(cylinder.axis,
				vec4_dot(ray.direction, cylinder.axis)));
	delta_p = vec4_sub(ray.origin, cylinder.center);
	delta_p_perp = vec4_sub(delta_p,
			vec4_scale(cylinder.axis,
				vec4_dot(delta_p, cylinder.axis)));
	a = vec4_dot(direction, direction);
	if (a < EPSILON)
		return (false); // rayo paralelo a axis → no hay cuerpo (pero sí podría haber tapas)
	b = 2.0f * vec4_dot(direction, delta_p_perp);
	c = vec4_dot(delta_p_perp, delta_p_perp)
		- (cylinder.radius * cylinder.radius);
	discrim = b * b - 4 * a * c;
	if (discrim < 0)
		return (false);
	sqrt_disc = sqrt(discrim);
	t0 = (-b - sqrt_disc) / (2.0f * a);
	t1 = (-b + sqrt_disc) / (2.0f * a);
	if (t0 > t1)
	{
		tmp = t0; //ver
		t0 = t1;
		t1 = tmp;
	}
	if (t0 > 0)
		*t_body = t0;
	else if (t1 > 0)
		*t_body = t1;
	else
		return (false);
	p = vec4_add(ray.origin, vec4_scale(ray.direction, *t_body));
	proj = vec4_dot(vec4_sub(p, cylinder.center), cylinder.axis);
// Si el height es muy grande en comparación con radius, los errores de punto
// flotante podrían hacer fallar el test de altura. se agrega EPSILON 
	if (proj < -cylinder.height / 2.0f - EPSILON || proj > cylinder.height / 2.0f + EPSILON)
		return (false);
	*normal_body = vec4_normalize(
			vec4_sub(p, vec4_add(cylinder.center,
					vec4_scale(cylinder.axis, proj))));
	return (true);
}

// ----------------------------------
// Intersección con una tapa
// ----------------------------------
static bool	mrt_hit_cylinder_cap(t_ray ray, t_cylinder cylinder, float *t_cap,t_vec4 *normal_cap, bool top)
{
	t_vec4	cap_center;
	t_vec4	n;
	float	denom;
	float	t;
	t_vec4	p;
	float	dist;

	*t_cap = INFINITY;
	*normal_cap = (t_vec4){0, 0, 0, 0};
	if (top)
		cap_center = vec4_add(cylinder.center, vec4_scale(cylinder.axis,
					cylinder.height / 2.0f));
	else
		cap_center = vec4_sub(cylinder.center, vec4_scale(cylinder.axis,
					cylinder.height / 2.0f));
	n = vec4_normalize(cylinder.axis);
	if (!top)
		n = vec4_scale(n, -1.0f); // normal hacia afuera en la base inferior
	denom = vec4_dot(ray.direction, n);
	if (fabs(denom) < 1e-6f) // paralelo al plano
		return (false);
	t = vec4_dot(vec4_sub(cap_center, ray.origin), n) / denom;
	if (t < 0)
		return (false);
	p = vec4_add(ray.origin, vec4_scale(ray.direction, t));
	dist = sqrtf(vec4_dot(vec4_sub(p, cap_center), (vec4_sub(p, cap_center))));
	if (dist > cylinder.radius)
		return (false);
	*t_cap = t;
	*normal_cap = n;
	return (true);
}

// ----------------------------------
// Intersección completa cilindro
// ----------------------------------
bool	mrt_hit_cylinder(t_ray ray, t_cylinder cylinder, t_hittable **hit)
{
	bool	hit_body;
	bool	hit_cap_base;
	bool	hit_cap_top;
	float	t_body;
	float	t_cap_base;
	float	t_cap_top;
	t_vec4	normal_body;
	t_vec4	normal_cap_base;
	t_vec4	normal_cap_top;
	float	t_final;
	t_vec4	normal_final;

	// 1. cuerpo
	hit_body = mrt_hit_cylinder_body(ray, cylinder, &t_body, &normal_body);
	// 2. tapa base
	hit_cap_base = mrt_hit_cylinder_cap(ray, cylinder, &t_cap_base,
			&normal_cap_base, false);
	// 3. tapa superior
	hit_cap_top = mrt_hit_cylinder_cap(ray, cylinder, &t_cap_top,
			&normal_cap_top, true);
	// Inicializar
	t_final = INFINITY;
	normal_final = (t_vec4){0, 0, 0, 0};
	// Seleccionar el menor t válido
	if (hit_body && t_body < t_final)
	{
		t_final = t_body;
		normal_final = normal_body;
	}
	if (hit_cap_base && t_cap_base < t_final)
	{
		t_final = t_cap_base;
		normal_final = normal_cap_base;
	}
	if (hit_cap_top && t_cap_top < t_final)
	{
		t_final = t_cap_top;
		normal_final = normal_cap_top;
	}
	if (t_final == INFINITY)
		return (false);
	// llenar hittable
	(*hit)->t = t_final;
	(*hit)->point = vec4_add(ray.origin, vec4_scale(ray.direction, t_final));
	(*hit)->normal = normal_final;
	return (true);
}

/* bool	mrt_hit_cylinder_body(t_ray ray, t_cylinder cylinder, float *t)
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
} */
