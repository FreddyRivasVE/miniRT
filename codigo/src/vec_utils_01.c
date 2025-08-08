/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:02:04 by brivera           #+#    #+#             */
/*   Updated: 2025/08/06 21:58:29 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Forzamos w = 0
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

/* 
 * Normaliza un vector
 * Devuelve un nuevo vector con la misma dirección que 'v' pero de longitud 1.
 * Si el vector tiene longitud cero, se devuelve un vector nulo.
 * 
 * Calcula la longitud (norma euclídea) del vector en 3D: sqrtf(x² + y² + z²)
 * len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
 * 
 * Divide las primeras tres componentes por la longitud
 * para obtener un vector unitario. La componente w queda igual.
 * 
*/

t_vec4	vec4_normalize(t_vec4 v)
{
	float	len;

	len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (len == 0.0f)
		return ((t_vec4){0, 0, 0, 0});
	return ((t_vec4){v[0] / len, v[1] / len, v[2] / len, v[3]});
}

t_vec4	vec4_create(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}

/**
 * Calcula el producto vectorial (cross product) entre dos vectores 3D.
 *
 * El producto vectorial de dos vectores a y b da como resultado un nuevo vector 
 * perpendicular a ambos
 * Es útil en gráficos 3D para obtener normales a superficies, calcular 
 * orientaciones y rotaciones.
 *
 * Fórmula
 * Para dos vectores a = (a_x, a_y, a_z) y b = (b_x, b_y, b_z),
 * el producto vectorial es:
 * 
 *      a × b = (a_y * b_z - a_z * b_y,
 *               a_z * b_x - a_x * b_z,
 *               a_x * b_y - a_y * b_x)
 *
 * Nota: La componente w se fija en 0, ya que el resultado
 * es un vector direccional.
 *
 * @param a Primer vector (t_vec4) con componentes x, y, z, w
 * @param b Segundo vector (t_vec4) con componentes x, y, z, w
 * @return Vector resultante (t_vec4) perpendicular a a y b
 */

t_vec4	vec4_cross(t_vec4 a, t_vec4 b)
{
	return (vec4_create(a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0],
			0.0f));
}
