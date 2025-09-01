/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_hit_objects_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:26:18 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 19:13:57 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static bool	mrt_check_sphere_hit(t_scene_node *node, t_hit_context *ctx)
{
	if (node->type == SPHERE)
	{
		if (mrt_hit_sphere(ctx->ray, *(t_sphere *)node->object, &node->hit)
			&& node->hit->t < *ctx->t_closest && node->hit->t > EPSILON)
		{
			*ctx->t_closest = node->hit->t;
			*ctx->h_color = mrt_light_color(ctx->elements, node->hit, ctx->ray);
			return (true);
		}
	}
	return (false);
}

static bool	mrt_check_plane_hit(t_scene_node *node, t_hit_context *ctx)
{
	t_vec4	base_color;

	if (node->type == PLANE)
	{
		if (mrt_hit_plane(ctx->ray, *(t_plane *)node->object, &node->hit)
			&& node->hit->t < *ctx->t_closest && node->hit->t > EPSILON)
		{
			*ctx->t_closest = node->hit->t;
			base_color = mrt_light_color(ctx->elements, node->hit, ctx->ray);
			*ctx->h_color = mrt_apply_checkerboard_pattern(ctx->elements,
					base_color, node->hit, node);
			return (true);
		}
	}
	return (false);
}

static bool	mrt_check_cylinder_hit(t_scene_node *node, t_hit_context *ctx)
{
	if (node->type == CYLINDER)
	{
		if (mrt_hit_cylinder(ctx->ray, *(t_cylinder *)node->object, &node->hit)
			&& node->hit->t < *ctx->t_closest && node->hit->t > EPSILON)
		{
			*ctx->t_closest = node->hit->t;
			*ctx->h_color = mrt_light_color(ctx->elements, node->hit, ctx->ray);
			return (true);
		}
	}
	return (false);
}

static bool	mrt_check_cone_hit(t_scene_node *node, t_hit_context *ctx)
{
	if (node->type == CONE)
	{
		if (mrt_hit_cone(ctx->ray, *(t_cone *)node->object, &node->hit)
			&& node->hit->t < *ctx->t_closest && node->hit->t > EPSILON)
		{
			*ctx->t_closest = node->hit->t;
			*ctx->h_color = mrt_light_color(ctx->elements, node->hit, ctx->ray);
			return (true);
		}
	}
	return (false);
}

void	mrt_check_object_hit(t_scene_node *node, t_hit_context *ctx)
{
	mrt_check_sphere_hit(node, ctx);
	mrt_check_plane_hit(node, ctx);
	mrt_check_cylinder_hit(node, ctx);
	mrt_check_cone_hit(node, ctx);
}
