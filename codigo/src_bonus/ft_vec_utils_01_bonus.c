/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils_01_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:02:12 by brivera           #+#    #+#             */
/*   Updated: 2025/09/02 16:53:16 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Clamps the components of a 4D vector between a minimum and maximum value.
 *
 * Each of the first three components (x, y, z) of the input vector 'v'
 * is restricted to the range [min, max]. Any values below 'min' are set 
 * to 'min', and values above 'max' are set to 'max'.
 *
 * The w component of the resulting vector is set to 0.0f.
 *
 * @param v   Input vector (t_vec4).
 * @param min Minimum clamp value.
 * @param max Maximum clamp value.
 * @return    A new vector (t_vec4) with clamped components.
 */

t_vec4	vec4_clamp(t_vec4 v, float min, float max)
{
	t_vec4	result;

	result[0] = fminf(fmaxf(v[0], min), max);
	result[1] = fminf(fmaxf(v[1], min), max);
	result[2] = fminf(fmaxf(v[2], min), max);
	result[3] = 0.0f;
	return (result);
}

t_vec4	vec4_mul(t_vec4 a, t_vec4 b)
{
	t_vec4	result;

	result[0] = a[0] * b[0];
	result[1] = a[1] * b[1];
	result[2] = a[2] * b[2];
	result[3] = 0.0f;
	return (result);
}

float	vect4_length(t_vec4 v)
{
	float	r;

	r = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	return (r);
}

/* 
 * Normalizes a vector
 * Returns a new vector with the same direction as 'v' but with length 1.
 * If the vector has zero length, a null vector is returned.
 * 
 * Computes the length (Euclidean norm) of the 3D vector: sqrtf(x² + y² + z²)
 * len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
 * 
 * Divides the first three components by the length
 * to obtain a unit vector. The w component remains unchanged.
 * 
*/

t_vec4	vec4_normalize(t_vec4 v)
{
	float	len;

	len = vect4_length(v);
	if (len == 0.0f)
		return ((t_vec4){0, 0, 0, 0});
	return ((t_vec4){v[0] / len, v[1] / len, v[2] / len, v[3]});
}

t_vec4	vec4_create(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}
