/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils_01_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:02:12 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 13:14:14 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

	len = vect4_length(v);
	if (len == 0.0f)
		return ((t_vec4){0, 0, 0, 0});
	return ((t_vec4){v[0] / len, v[1] / len, v[2] / len, v[3]});
}

t_vec4	vec4_create(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}
