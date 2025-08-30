/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_ray_color_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:26:59 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 13:15:18 by frivas           ###   ########.fr       */
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
	if (node->type == PLANE)
	{
		if (mrt_hit_plane(ctx->ray, *(t_plane *)node->object, &node->hit)
			&& node->hit->t < *ctx->t_closest && node->hit->t > EPSILON)
		{
			*ctx->t_closest = node->hit->t;
			*ctx->h_color = mrt_light_color(ctx->elements, node->hit, ctx->ray);
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

static void	mrt_check_object_hit(t_scene_node *node, t_hit_context *ctx)
{
	mrt_check_sphere_hit(node, ctx);
	mrt_check_plane_hit(node, ctx);
	mrt_check_cylinder_hit(node, ctx);
}

t_vec4	mrt_ray_color(t_ray *ray, t_data *elements)
{
	t_scene_node	*current;
	t_hit_context	ctx;
	t_vec4			hit_color;
	float			t_final;

	hit_color = (t_vec4){0, 0, 0, 0};
	t_final = INFINITY;
	ctx.ray = ray;
	ctx.elements = elements;
	ctx.h_color = &hit_color;
	ctx.t_closest = &t_final;
	current = elements->objects;
	while (current)
	{
		mrt_check_object_hit(current, &ctx);
		current = current->next;
	}
	return (hit_color);
}
