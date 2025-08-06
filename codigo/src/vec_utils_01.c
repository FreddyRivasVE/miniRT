/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-06 13:02:04 by brivera           #+#    #+#             */
/*   Updated: 2025-08-06 13:02:04 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	vec4_create(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}

/**
 * Calcula el producto vectorial (cross product) entre dos vectores 3D.
 *
 * El producto vectorial de dos vectores a y b da como resultado un nuevo vector 
 * perpendicular a ambos, siguiendo la regla de la mano derecha.
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

t_vec4 vec4_cross(t_vec4 a, t_vec4 b)
{
	return vec4_create(
		a[1] * b[2] - a[2] * b[1],
		a[2] * b[0] - a[0] * b[2],
		a[0] * b[1] - a[1] * b[0],
		0.0f);
}
