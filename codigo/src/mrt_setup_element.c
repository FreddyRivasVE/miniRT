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

// t_camera	*setup_test_camera(void)
// {
// 	t_camera	*cam;

// 	cam = ft_calloc(1, sizeof(t_camera));
// 	if (!cam)
// 		return (NULL);
// 	cam->origin = vec4_create(0.0f, 0.0f, 0.0f, 1.0f);
// 	cam->direction = vec4_create(0.0f, 0.0f, -1.0f, 0.0f);
// 	cam->fov = 70.0f;
// 	return (cam);
// }

//L <x,y,z> <brightness> <R,G,B>
// t_point_light	*setup_test_light(void)
// {
// 	t_point_light	*light;

// 	light = ft_calloc(1, sizeof(t_point_light));
// 	if (!light)
// 		return (NULL);
// 	*light = (t_point_light){
// 		.position = vec4_create(10, 10, 10, 1),
// 		.diff_color = vec4_create(1, 1, 1, 0),
// 		.diff_power = 0.9f,
// 		.spec_color = vec4_create(1, 1, 1, 0),
// 		.spec_power = 1.0f
// 	};
// 	return (light);
// }

// t_ambient	*setup_test_ambient(void)
// {
// 	t_ambient	*amb;

// 	amb = ft_calloc(1, sizeof(t_ambient));
// 	if (!amb)
// 		return (NULL);
// 	amb->ratio = 0.1;
// 	amb->color = vec4_create(0.5, 0.5, 0.5, 0);
// 	return (amb);
// }

// t_sphere	*setup_test_sphere(t_vec4 center, float radius)
// {
// 	t_sphere	*sp;

// 	sp = ft_calloc(1, sizeof(t_sphere));
// 	if (!sp)
// 		return (NULL);
// 	sp->center = center;
// 	sp->radius = radius;
// 	return (sp);
// }

// t_plane	*setup_test_plane(void)
// {
// 	t_plane	*pl;

// 	pl = ft_calloc(1, sizeof(t_plane));
// 	if (!pl)
// 		return (NULL);
// 	pl->point = vec4_create(0, -1, 0, 1);
// 	pl->normal = vec4_create(0, 1, 0, 0);
// 	return (pl);
// }

t_ambient	*mrt_setup_ambient(char **r_amb)
{
	t_ambient	*amb;

	amb = ft_calloc(1, sizeof(t_ambient));
	if (!amb)
		return (NULL);
	amb->ratio = ft_atof(r_amb[1]);
	amb->color = mrt_extrac_color(r_amb[2]);
	return (amb);
}

t_camera	*mrt_setup_camera(char **r_cam)
{
	t_camera	*cam;

	cam = ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->origin = mrt_extrac_vector(r_cam[1], 0.0f);
	cam->direction = mrt_extrac_vector(r_cam[2], 0.0f);
	cam->fov = ft_atof(r_cam[3]);
	return (cam);
}

t_point_light	*mrt_setup_light(char **r_light)
{
	t_point_light	*light;

	light = ft_calloc(1, sizeof(t_point_light));
	if (!light)
		return (NULL);
	*light = (t_point_light){
		.position = mrt_extrac_vector(r_light[1], 1.0f), //por que w vale 1?
		.diff_color = vec4_create(1, 1, 1, 0), //validar con Brenda de donde sale este dato.
		.diff_power = 0.9f, //aqui va el valor de brillo de la luz que esta en el .rt?
		.spec_color = vec4_create(1, 1, 1, 0), //validar con Brenda de donde sale este dato.
		.spec_power = 1.0f //validar con Brenda de donde sale este dato.
	};
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
	*rgb = mrt_extrac_color(r_sphere[3]);
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
	*rgb = mrt_extrac_color(r_plane[3]);
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
	*rgb = mrt_extrac_color(r_cylinder[5]);
	return (cy);
}