/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_setup_element.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:24:46 by brivera           #+#    #+#             */
/*   Updated: 2025/08/07 13:43:04 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	*setup_test_camera(void)
{
	t_camera	*cam;

	cam = ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->origin = vec4_create(0.0f, 0.0f, 0.0f, 1.0f);
	cam->direction = vec4_create(0.0f, 0.0f, -1.0f, 0.0f);
	cam->fov = 70.0f;
	return (cam);
}

//L <x,y,z> <brightness> <R,G,B>
t_point_light	*setup_test_light(void)
{
	t_point_light	*light;

	light = ft_calloc(1, sizeof(t_point_light));
	if (!light)
		return (NULL);
	*light = (t_point_light){
		.position = vec4_create(10, 10, 10, 1),
		.diff_color = vec4_create(1, 1, 1, 0),
		.diff_power = 0.9f,
		.spec_color = vec4_create(1, 1, 1, 0),
		.spec_power = 1.0f
	};
	return (light);
}

t_ambient	*setup_test_ambient(void)
{
	t_ambient	*amb;

	amb = ft_calloc(1, sizeof(t_ambient));
	if (!amb)
		return (NULL);
	amb->ratio = 0.1;
	amb->color = vec4_create(0.5, 0.5, 0.5, 0);
	return (amb);
}

t_sphere	*setup_test_sphere(t_vec4 center, float radius)
{
	t_sphere	*sp;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	return (sp);
}

t_plane	*setup_test_plane(void)
{
	t_plane	*pl;

	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->point = vec4_create(0, -1, 0, 1);
	pl->normal = vec4_create(0, 1, 0, 0);
	return (pl);
}
