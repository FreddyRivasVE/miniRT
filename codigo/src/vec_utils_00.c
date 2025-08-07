/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:19:37 by brivera           #+#    #+#             */
/*   Updated: 2025/08/07 00:14:38 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calcula el vector reflejado de un vector incidente respecto
 * a una normal.
 * Ambos vectores se normalizan antes de calcular la reflexión
 * para asegurar
 * que el resultado sea correcto.
 *
 * @param v Vector incidente (t_vec4)
 * @param n Vector normal de la superficie (t_vec4)
 * @return Vector reflejado (t_vec4)
 */
t_vec4	vec4_reflect(t_vec4 v, t_vec4 n)
{
	t_vec4	v_norm;
	t_vec4	n_norm;
	float	dot;
	t_vec4	scaled_normal;
	t_vec4	reflected;

	v_norm = vec4_normalize(v);
	n_norm = vec4_normalize(n);
	dot = vec4_dot(v_norm, n_norm);
	scaled_normal = vec4_scale(n_norm, 2.0f * dot);
	reflected = vec4_sub(v_norm, scaled_normal);
	return (reflected);
}

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
