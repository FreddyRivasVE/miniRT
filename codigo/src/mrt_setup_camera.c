/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_setup_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:52:21 by brivera           #+#    #+#             */
/*   Updated: 2025/08/21 13:54:33 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_camera_view	mrt_compute_camera_view(t_camera *cam, t_window win)
{
	t_camera_view	view;
	float			aspect_ratio;
	float			theta;
	float			h;
	float			viewport_height;
	float			viewport_width;
	t_vec4			world_up;
	t_vec4			forward;
	t_vec4			right;
	t_vec4			up_cam;
	float			focal_length;
	t_vec4			horiz_offset;
	t_vec4			vert_offset;
	// Relación de aspecto y parámetros del viewport
	aspect_ratio = (float)win.width / (float)win.height;
	theta = cam->fov * PI / 180.0f; // FOV en radianes
	h = tanf(theta / 2.0f);
	viewport_height = 2.0f * h;
	viewport_width = aspect_ratio * viewport_height;
	// Posición de la cámara
	view.origin = cam->origin;
	// Base ortonormal de la cámara
	world_up = vec4_create(0.0f, 1.0f, 0.0f, 0.0f);
	forward = vec4_normalize(cam->direction); // mirando hacia adelante
	right = vec4_normalize(vec4_cross(forward, world_up));
	up_cam = vec4_cross(right, forward);
	// Escalamos los vectores horizontal y vertical del viewport
	view.horizontal = vec4_scale(right, viewport_width);
	view.vertical = vec4_scale(up_cam, viewport_height);
	// Distancia focal: controla el "zoom" real
	focal_length = 1.0f;
	// Calculamos la esquina inferior izquierda del viewport
	horiz_offset = vec4_scale(view.horizontal, 0.5f);
	vert_offset = vec4_scale(view.vertical, 0.5f);
	view.bottom_left_corner = view.origin;
	view.bottom_left_corner = vec4_sub(view.bottom_left_corner, horiz_offset);
	view.bottom_left_corner = vec4_sub(view.bottom_left_corner, vert_offset);
	view.bottom_left_corner = vec4_add(view.bottom_left_corner,
			vec4_scale(forward, focal_length));
	return (view);
}
