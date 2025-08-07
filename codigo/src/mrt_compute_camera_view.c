/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_compute_camera_view.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-07 15:47:26 by brivera           #+#    #+#             */
/*   Updated: 2025-08-07 15:47:26 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera_view	mrt_compute_camera_view(t_camera *cam)
{
	t_camera_view	view;
	t_vec4			up;
	t_vec4			camera_forward;
	t_vec4			camera_right;
	t_vec4			camera_up;
	t_vec4			half_horiz;
	t_vec4			half_vert;
	double			theta;
	double			half_height;
	double			half_width;

	view.origin = cam->origin;
	theta = cam->fov * (PI / 180.0);
	half_height = tan(theta / 2.0);
	half_width = ASPECT_RATIO * half_height;
	up = vec4_create(0, 1, 0, 0);
	camera_forward = vec4_normalize(vec4_scale(cam->direction, -1));
	camera_right = vec4_normalize(vec4_cross(up, camera_forward));
	camera_up = vec4_cross(camera_forward, camera_right);
	view.horizontal = vec4_scale(camera_right, 2.0 * half_width);
	view.vertical = vec4_scale(camera_up, 2.0 * half_height);
	half_horiz = vec4_scale(view.horizontal, 0.5);
	half_vert = vec4_scale(view.vertical, 0.5);
	view.bottom_left_corner = \
		vec4_sub(vec4_sub(vec4_sub(view.origin, half_horiz),half_vert),camera_forward);
	return (view);
}
