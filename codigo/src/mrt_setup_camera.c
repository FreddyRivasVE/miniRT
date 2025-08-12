/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_setup_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-11 11:52:21 by brivera           #+#    #+#             */
/*   Updated: 2025-08-11 11:52:21 by brivera          ###   ########.fr       */
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
	cam->direction = mrt_extrac_vector(r_cam[2], 0.0f);
	cam->fov = ft_atof(r_cam[3]);
	return (cam);
}

t_camera_view mrt_compute_camera_view(t_camera *cam, t_window window)
{
    t_camera_view  view;
    t_vec4         up;
    t_vec4         camera_forward;
    t_vec4         camera_right;
    t_vec4         camera_up;
    float          aspect_ratio;
    float          viewport_height;
    float          viewport_width;
    float          half_height;
    float          half_width;

    // 1. Configuración básica
    aspect_ratio = (float)window.width / (float)window.height;
    up = vec4_create(0, 1, 0, 0);
    view.origin = cam->origin;

    // 2. Calcular dimensiones del viewport
    float fov_rad = cam->fov * (PI / 180.0f);
    viewport_height = 2.0f * tanf(fov_rad / 2.0f);
    viewport_width = viewport_height * aspect_ratio;

    // 3. Establecer ejes de la cámara
    camera_forward = vec4_normalize(vec4_scale(cam->direction, -1.0f));
    
    // Manejar caso cuando la cámara mira directamente arriba/abajo
    if (fabsf(vec4_dot(camera_forward, up)) > 0.999f)
        camera_right = vec4_create(1.0f, 0.0f, 0.0f, 0.0f);
    else
        camera_right = vec4_normalize(vec4_cross(up, camera_forward));
    
    camera_up = vec4_cross(camera_forward, camera_right);

    // 4. Calcular vectores del viewport
    view.horizontal = vec4_scale(camera_right, viewport_width);
    view.vertical = vec4_scale(camera_up, viewport_height);

    // 5. Calcular esquina inferior izquierda
    half_width = viewport_width / 2.0f;
    half_height = viewport_height / 2.0f;
    
    t_vec4 horiz_offset = vec4_scale(view.horizontal, 0.5f);
    t_vec4 vert_offset = vec4_scale(view.vertical, 0.5f);
    
    view.bottom_left_corner = vec4_sub(view.origin, horiz_offset);
    view.bottom_left_corner = vec4_sub(view.bottom_left_corner, vert_offset);
    view.bottom_left_corner = vec4_sub(view.bottom_left_corner, camera_forward);

    return view;
}
