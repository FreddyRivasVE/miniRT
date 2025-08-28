/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_utils_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:14:01 by brivera           #+#    #+#             */
/*   Updated: 2025/08/28 16:14:13 by brivera          ###   ########.fr       */
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
