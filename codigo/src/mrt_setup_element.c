/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_setup_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:24:46 by brivera           #+#    #+#             */
/*   Updated: 2025/08/24 10:37:25 by frivas           ###   ########.fr       */
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

t_light	*mrt_setup_light(char **r_light)
{
	t_light	*light;

	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (NULL);
	light->position = mrt_extrac_vector(r_light[1], 1.0f);
	light->brightness_r = ft_atof(r_light[2]);
	if (r_light[3])
		light->color = mrt_extract_color(r_light[3]);
	else
		light->color = vec4_create(1, 1, 1, 0);
	return (light);
}

t_sphere	*mrt_setup_sphere(char **r_sphere, t_vec4 *rgb)
{
	t_sphere	*sp;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = mrt_extrac_vector(r_sphere[1], 1.0f);
	sp->radius = ft_atof(r_sphere[2]) * 0.5f;
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
	pl->normal = vec4_normalize(mrt_extrac_vector(r_plane[2], 0.0f));
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
	cy->axis = vec4_normalize(mrt_extrac_vector(r_cylinder[2], 0.0f));
	cy->radius = ft_atof(r_cylinder[3]) * 0.5f;
	cy->height = ft_atof(r_cylinder[4]);
	*rgb = mrt_extract_color(r_cylinder[5]);
	return (cy);
}
