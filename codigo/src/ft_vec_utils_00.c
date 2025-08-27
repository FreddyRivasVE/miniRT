/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:02:03 by brivera           #+#    #+#             */
/*   Updated: 2025/08/27 11:58:28 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calcula el producto escalar (dot product) entre dos vectores 3D.
 *
 * @param a Primer vector de tipo t_vec4.
 * @param b Segundo vector de tipo t_vec4.
 * @return Un número flotante que representa el producto escalar
 * entre a y b.
 *
 * Solo se consideran las componentes X, Y y Z
 * de los vectores (a[0], a[1], a[2]),
 * ya que la componente W no se usa en cálculos 
 * geométricos tradicionales.
 *
 * El producto escalar se usa, por ejemplo, para:
 * - Determinar el ángulo entre dos vectores
 * - Calcular proyecciones
 * - Evaluar intersecciones en ray tracing
 *
 * Si el resultado es 0, los vectores son ortogonales
 * (perpendiculares).
 */
float	vec4_dot(t_vec4 a, t_vec4 b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

/* 
 * Escala un vector por un escalar: v * s
 * Multiplica cada componente del vector 'v' por el escalar 's'.
 * Devuelve un nuevo vector con los resultados.
 * Se multiplica cada componente del vector por el escalar
 *
*/

t_vec4	vec4_scale(t_vec4 v, float s)
{
	return ((t_vec4){v[0] * s, v[1] * s, v[2] * s, v[3] * s});
}

/* 
 * Suma de vectores: a + b
 * Realiza la suma componente a componente de los vectores 'a' y 'b'.
 * Devuelve un nuevo vector con la suma de cada componente.
 * 
 */

t_vec4	vec4_add(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]});
}
/*
 * Resta dos vectores de 4 componentes.
 * 
 * Primer vector (minuendo)
 * b Segundo vector (sustraendo)
 * Vector resultante de la resta (a - b)
 */

t_vec4	vec4_sub(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]});
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
