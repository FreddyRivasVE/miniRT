/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_pattern_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:00:00 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 19:44:32 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	mrt_get_plane_checker_coords(t_vec4 normal, t_vec4 hit_point,
				float scale, int *coords)
{
	if (fabs(normal[1]) > (1.0f - E_NORMAL))
	{
		coords[0] = (int)floor(hit_point[0] / scale);
		coords[1] = (int)floor(hit_point[2] / scale);
	}
	else if (fabs(normal[0]) > (1.0f - E_NORMAL))
	{
		coords[0] = (int)floor(hit_point[1] / scale);
		coords[1] = (int)floor(hit_point[2] / scale);
	}
	else if (fabs(normal[2]) > (1.0f - E_NORMAL))
	{
		coords[0] = (int)floor(hit_point[0] / scale);
		coords[1] = (int)floor(hit_point[1] / scale);
	}
	else
	{
		coords[0] = (int)floor(hit_point[0] / scale);
		coords[1] = (int)floor(hit_point[2] / scale);
	}
}

static t_vec4	mrt_apply_plane_checkerboard(t_vec4 base_color,
				t_vec4 hit_point, t_vec4 normal, float scale)
{
	int	coords[2];

	mrt_get_plane_checker_coords(normal, hit_point, scale, coords);
	if ((coords[0] + coords[1]) % 2 == 0)
		return (base_color);
	else
		return ((t_vec4){0.1, 0.1, 0.1, 1.0});
}

static bool	mrt_is_plane_object(t_scene_node *current)
{
	return (current && current->type == PLANE);
}

t_vec4	mrt_apply_checkerboard_pattern(t_data *data, t_vec4 base_color,
			t_hit *hit, t_scene_node *current)
{
	if (!data->checkerboard)
		return (base_color);
	if (!mrt_is_plane_object(current))
		return (base_color);
	return (mrt_apply_plane_checkerboard(base_color, hit->point,
			hit->normal, CHECKERBOARD_SCALE));
}
