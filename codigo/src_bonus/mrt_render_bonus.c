/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_render_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:28:11 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 13:15:23 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	mrt_put_color(t_vec4 color, int x, int y, t_window window)
{
	t_vec4		clamped;
	uint8_t		*pixels;
	int			index;

	clamped = vec4_clamp(color, 0.0f, 0.999f);
	index = (y * window.width + x) * 4;
	pixels = window.image->pixels;
	pixels[index] = (uint8_t)(255.99f * clamped[0]);
	pixels[index + 1] = (uint8_t)(255.99f * clamped[1]);
	pixels[index + 2] = (uint8_t)(255.99f * clamped[2]);
	pixels[index + 3] = 255;
}

t_ray	mrt_create_ray(t_vec4 origen, t_vec4 direction)
{
	t_ray	ray;

	ray.direction = direction;
	ray.origin = origen;
	return (ray);
}

t_ray	mrt_generate_ray(t_camera_view cam, float x, float y, t_window window)
{
	t_vec4	point_on_plane;
	t_vec4	direction;
	float	u;
	float	v;

	u = (float)(x + 0.5f) / (float)(window.width - 1);
	v = (float)(y + 0.5f) / (float)(window.height - 1);
	v = 1.0f - v;
	u = 1.0f - u;
	point_on_plane = cam.bottom_left_corner;
	point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.horizontal, u));
	point_on_plane = vec4_add(point_on_plane, vec4_scale(cam.vertical, v));
	direction = vec4_normalize(vec4_sub(point_on_plane, cam.origin));
	return (mrt_create_ray(cam.origin, direction));
}

static t_vec4	mrt_render_with_msaa(t_camera_view cam, int coords[2],
					t_window window, t_data *elements)
{
	t_vec4	color;
	t_ray	ray;
	float	offsets[4][2];
	int		sample;

	offsets[0][0] = 0.25f;
	offsets[0][1] = 0.25f;
	offsets[1][0] = 0.75f;
	offsets[1][1] = 0.25f;
	offsets[2][0] = 0.25f;
	offsets[2][1] = 0.75f;
	offsets[3][0] = 0.75f;
	offsets[3][1] = 0.75f;
	color = (t_vec4){0.0f, 0.0f, 0.0f, 0.0f};
	sample = 0;
	while (sample < 4)
	{
		ray = mrt_generate_ray(cam, (float)coords[0] + offsets[sample][0],
				(float)coords[1] + offsets[sample][1], window);
		color = vec4_add(color, mrt_ray_color(&ray, elements));
		sample++;
	}
	return (vec4_scale(color, 0.25f));
}

void	mrt_draw_to_window(t_window window, t_data *elements)
{
	t_camera_view	camera;
	t_ray			ray;
	t_vec4			color;
	int				coords[2];

	coords[1] = 0;
	camera = mrt_compute_camera_view(elements->camera, window);
	while (coords[1] < window.height)
	{
		coords[0] = 0;
		while (coords[0] < window.width)
		{
			if (ANTIALIASING == 1)
				color = mrt_render_with_msaa(camera, coords, window, elements);
			else
			{
				ray = mrt_generate_ray(camera, (float)coords[0],
						(float)coords[1], window);
				color = mrt_ray_color(&ray, elements);
			}
			mrt_put_color(color, coords[0], coords[1], window);
			coords[0]++;
		}
		coords[1]++;
	}
}
