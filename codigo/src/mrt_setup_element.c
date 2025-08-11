/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_setup_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:24:46 by brivera           #+#    #+#             */
/*   Updated: 2025/08/10 20:48:36 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ambient	*mrt_setup_ambient(char **r_amb)
{
	t_ambient	*amb;

	amb = ft_calloc(1, sizeof(t_ambient));
	if (!amb)
		return (NULL);
	amb->ratio = ft_atof(r_amb[1]);
	amb->color = mrt_extract_color(r_amb[2]);
	return (amb);
}

/**
 * @param r_light
 * Array de strings con los parámetros de la luz en este orden:
 *    - r_light[0]: Identificador (no usado, debe ser "L").
 *    - r_light[1]: Coordenadas de posición en formato "x,y,z".
 *    - r_light[2]: Intensidad difusa (brightness) en rango [0.0, 1.0].
 *    - r_light[3]: (Opcional) Color RGB en formato "R,G,B" (0-255).
 *       Si es NULL, se usa blanco (1,1,1).
* Configura los siguientes valores por defecto:
 *   - Color especular: Igual al color difuso (o blanco si no se especifica).
 *   - Intensidad especular (spec_power): 1.0 (valor básico para brillo suave).
 *   - Alpha (w) de colores: 0 (sin transparencia).
 * @warning No valida el rango de la intensidad difusa (debería ser [0.0, 1.0]).
 */

t_point_light *mrt_setup_light(char **r_light)
{
	t_point_light	*light;
	
	light = ft_calloc(1, sizeof(t_point_light));
	if (!light)
		return (NULL);
	light->position = mrt_extrac_vector(r_light[1], 1.0f);
	if (r_light[3])
		light->diff_color = mrt_extract_color(r_light[3]);
	else
		light->diff_color = vec4_create(1, 1, 1, 0);
	light->diff_power = ft_atof(r_light[2]);
	light->spec_color = light->diff_color;
	light->spec_power = 1.0f;
	return (light);
}

t_sphere	*mrt_setup_sphere(char **r_sphere, t_vec4 *rgb)
{
	t_sphere	*sp;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = mrt_extrac_vector(r_sphere[1], 1.0f);
	sp->radius = ft_atof(r_sphere[2]);
	*rgb = mrt_extract_color(r_sphere[3]);
	return (sp);
}

t_plane	*mrt_setup_plane(char **r_plane, t_vec4 *rgb)
{
	t_plane	*pl;

	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->point = mrt_extrac_vector(r_plane[1], 1.0f);
	pl->normal = mrt_extrac_vector(r_plane[2], 0.0f);
	*rgb = mrt_extract_color(r_plane[3]);
	return (pl);
}

t_cylinder	*mrt_setup_cylinder(char **r_cylinder, t_vec4 *rgb)
{
	t_cylinder	*cy;

	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->center = mrt_extrac_vector(r_cylinder[1], 1.0f);
	cy->axis = mrt_extrac_vector(r_cylinder[2], 0.0f);
	cy->radius = ft_atof(r_cylinder[3]);
	cy->angle = ft_atof(r_cylinder[4]);
	*rgb = mrt_extract_color(r_cylinder[5]);
	return (cy);
}
