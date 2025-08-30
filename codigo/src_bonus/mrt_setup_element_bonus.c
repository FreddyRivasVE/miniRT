/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_setup_element_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 21:24:46 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 13:15:26 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

t_camera	*mrt_setup_camera(char **r_cam)
{
	t_camera	*cam;

	cam = ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->origin = mrt_extrac_vector(r_cam[1], 0.0f);
	cam->direction = vec4_normalize(mrt_extrac_vector(r_cam[2], 0.0f));
	cam->fov = ft_atof(r_cam[3]);
	return (cam);
}
