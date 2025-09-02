/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils_00_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:02:03 by brivera           #+#    #+#             */
/*   Updated: 2025/09/02 16:52:48 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

/**
 * Computes the dot product between two 3D vectors.
 *
 * @param a First vector of type t_vec4.
 * @param b Second vector of type t_vec4.
 * @return A floating-point number representing the dot product
 * between a and b.
 *
 * Only the X, Y, and Z components of the vectors (a[0], a[1], a[2])
 * are considered, since the W component is not used in traditional
 * geometric calculations.
 *
 * The dot product is used, for example, to:
 * - Determine the angle between two vectors
 * - Compute projections
 * - Evaluate intersections in ray tracing
 *
 * If the result is 0, the vectors are orthogonal
 * (perpendicular).
 */
float	vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/* 
 * Scales a vector by a scalar: v * s
 * Multiplies each component of the vector 'v' by the scalar 's'.
 * Returns a new vector with the results.
 * Each component of the vector is multiplied by the scalar.
 *
 */

t_vec4	vec4_scale(t_vec4 v, float s)
{
	return ((t_vec4){v[0] * s, v[1] * s, v[2] * s, v[3] * s});
}

t_vec4	vec4_add(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]});
}
/*
 * Subtracts two 4-component vectors.
 * 
 * a First vector (minuend)
 * b Second vector (subtrahend)
 * Resulting vector from the subtraction (a - b)
 */

t_vec4	vec4_sub(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]});
}

/**
 * Computes the cross product between two 3D vectors.
 *
 * The cross product of two vectors a and b results in a new vector 
 * that is perpendicular to both.
 * It is useful in 3D graphics to obtain surface normals, calculate 
 * orientations, and perform rotations.
 *
 * Formula
 * For two vectors a = (a_x, a_y, a_z) and b = (b_x, b_y, b_z),
 * the cross product is:
 * 
 *      a × b = (a_y * b_z - a_z * b_y,
 *               a_z * b_x - a_x * b_z,
 *               a_x * b_y - a_y * b_x)
 *
 * Note: The w component is set to 0, since the result
 * is a directional vector.
 *
 * @param a First vector (t_vec4) with components x, y, z, w
 * @param b Second vector (t_vec4) with components x, y, z, w
 * @return Resulting vector (t_vec4) perpendicular to both a and b
 */

t_vec4	vec4_cross(t_vec4 a, t_vec4 b)
{
	return (vec4_create(a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0],
			0.0f));
}
