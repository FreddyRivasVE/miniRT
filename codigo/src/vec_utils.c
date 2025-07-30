/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-30 10:50:20 by brivera           #+#    #+#             */
/*   Updated: 2025-07-30 10:50:20 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
 * Escala un vector por un escalar: v * s
 * Multiplica cada componente del vector 'v' por el escalar 's'.
 * Devuelve un nuevo vector con los resultados.
 * Se multiplica cada componente del vector por el escalar
 *
*/

t_vec4  vec4_scale(t_vec4 v, float s)
{
	return ((t_vec4){v[0] * s, v[1] * s, v[2] * s, v[3] * s});
}

/* 
 * Suma de vectores: a + b
 * Realiza la suma componente a componente de los vectores 'a' y 'b'.
 * Devuelve un nuevo vector con la suma de cada componente.
 * 
 */

t_vec4  vec4_add(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]});
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

t_vec4  vec4_normalize(t_vec4 v)
{
	float   len;

	len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (len == 0.0f)
		return ((t_vec4){0, 0, 0, 0});
	return ((t_vec4){v[0] / len, v[1] / len, v[2] / len, v[3]});
}

