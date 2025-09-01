/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_light_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:02:03 by frivas            #+#    #+#             */
/*   Updated: 2025/09/01 18:40:44 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	mrt_push_light(t_light **light, t_light *new_node)
{
	t_light	*current;

	current = *light;
	if (!new_node || !light)
		return (0);
	new_node->next = NULL;
	if (!*light)
	{
		*light = new_node;
		return (1);
	}
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (1);
}

void	mrt_set_ambient(t_data *el, t_hit *hit, t_vec4 *accum)
{
	t_vec4	amb;

	amb = (t_vec4){0, 0, 0, 0};
	if (el->ambient)
	{
		hit->material->ambient = vec4_scale(el->ambient->color,
				el->ambient->ratio);
		amb = hit->material->ambient;
	}
	*accum = amb;
}

void	mrt_setup_lighting_vectors(t_light *l, t_hit *hit,
		t_vec4 *light_dir, float *light_dist)
{
	t_vec4	light_to_point;

	light_to_point = vec4_sub(l->position, hit->point);
	*light_dist = vect4_length(light_to_point);
	*light_dir = vec4_normalize(light_to_point);
}

bool	mrt_intersect_scene(t_data *elements, t_ray *ray, t_hit *shadow_hit)
{
	t_scene_node	*current;
	float			closest_t;
	bool			hit_any;

	current = elements->objects;
	closest_t = INFINITY;
	hit_any = false;
	while (current)
	{
		if (mrt_object_hit_light(current, &closest_t, shadow_hit, ray))
			hit_any = true;
		current = current->next;
	}
	if (hit_any)
		shadow_hit->t = closest_t;
	return (hit_any);
}
