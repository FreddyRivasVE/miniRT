/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_camera_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-26 13:38:01 by brivera           #+#    #+#             */
/*   Updated: 2025-08-26 13:38:01 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mrt_compute_viewport(t_camera *cam, t_window win, float *height,
		float *width)
{
	float	aspect_ratio;
	float	theta;
	float	h;

	aspect_ratio = (float)win.width / (float)win.height;
	theta = cam->fov * PI / 180.0f;
	h = tanf(theta / 2.0f);
	*height = 2.0f * h;
	*width = aspect_ratio * (*height);
}

t_vec4	mtr_word_right(t_camera *cam, float viewport_width)
{
	t_vec4	world_up;
	t_vec4	forward;
	t_vec4	right;

	world_up = vec4_create(0.0f, 1.0f, 0.0f, 0.0f);
	forward = vec4_normalize(cam->direction);
	right = vec4_normalize(vec4_cross(forward, world_up));
	return (vec4_scale(right, viewport_width));
}

t_vec4	mtr_word_up(t_camera *cam, float viewport_height)
{
	t_vec4	world_up;
	t_vec4	forward;
	t_vec4	up_cam;
	t_vec4	right;

	world_up = vec4_create(0.0f, 1.0f, 0.0f, 0.0f);
	forward = vec4_normalize(cam->direction);
	right = vec4_normalize(vec4_cross(forward, world_up));
	up_cam = vec4_cross(right, forward);
	return (vec4_scale(up_cam, viewport_height));
}

t_camera_view	mrt_compute_camera_view(t_camera *cam, t_window win)
{
	t_camera_view	view;
	t_vec4			horiz_offset;
	t_vec4			vert_offset;
	float			viewport_height;
	float			viewport_width;

	mrt_compute_viewport(cam, win, &viewport_height, &viewport_width);
	view.origin = cam->origin;
	view.horizontal = mtr_word_right(cam, viewport_width);
	view.vertical = mtr_word_up(cam, viewport_height);
	horiz_offset = vec4_scale(view.horizontal, 0.5f);
	vert_offset = vec4_scale(view.vertical, 0.5f);
	view.bottom_left_corner = view.origin;
	view.bottom_left_corner = vec4_sub(view.bottom_left_corner, horiz_offset);
	view.bottom_left_corner = vec4_sub(view.bottom_left_corner, vert_offset);
	view.bottom_left_corner = vec4_add(view.bottom_left_corner,
			vec4_scale(vec4_normalize(cam->direction), FOCAL_LENGHT));
	return (view);
}
