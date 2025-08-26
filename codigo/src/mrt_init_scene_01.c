/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_init_scene_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:59:10 by brivera           #+#    #+#             */
/*   Updated: 2025/08/26 11:26:22 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mrt_reserve_memory_node(t_scene_node **new)
{
	*new = ft_calloc(1, sizeof(t_scene_node));
	if (!*new)
		return (0);
	(*new)->hit = ft_calloc(1, sizeof(t_hit));
	if (!(*new)->hit)
		return (0);
	(*new)->hit->material = ft_calloc(1, sizeof(t_material));
	if (!(*new)->hit->material)
		return (0);
	return (1);
}

int	mrt_push_object(t_scene_node **lst, t_type type, void *obj, t_vec4 rgb)
{
	t_scene_node	*new;
	t_scene_node	*last;

	if (!obj || !lst)
		return (0);
	if (!mrt_reserve_memory_node(&new))
		return (0);
	new->type = type;
	new->object = obj;
	new->hit->material->base_color = rgb;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	return (1);
}

int	mrt_init_scene(t_data *data, t_list **row_data)
{
	t_list		*node;
	char		**tokens;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;
	t_vec4		rgb;

	node = *row_data;
	ft_memset(data, 0, sizeof(t_data));
	while (node)
	{
		tokens = ft_split_space(node->content);
		if (!tokens)
			return (0);
		if (tokens[0][0] == 'A')
		{
			data->ambient = mrt_setup_ambient(tokens);
			if (!data->ambient)
				return (0);
		}
		else if (tokens[0][0] == 'C')
		{
			data->camera = mrt_setup_camera(tokens);
			if (!data->camera)
				return (0);
		}
		else if (tokens[0][0] == 'L')
		{
			data->light = mrt_setup_light(tokens);
			if (!data->light)
				return (0);
		}
		else if (tokens[0][0] == 's' && tokens[0][1] == 'p')
		{
			sp = mrt_setup_sphere(tokens, &rgb);
			if (!sp || !mrt_push_object(&data->objects, SPHERE, sp, rgb))
				return (0);
		}
		else if (tokens[0][0] == 'p' && tokens[0][1] == 'l')
		{
			pl = mrt_setup_plane(tokens, &rgb);
			if (!pl || !mrt_push_object(&data->objects, PLANE, pl, rgb))
				return (0);
		}
		else if (tokens[0][0] == 'c' && tokens[0][1] == 'y')
		{
			cy = mrt_setup_cylinder(tokens, &rgb);
			if (!cy || !mrt_push_object(&data->objects, CYLINDER, cy, rgb))
				return (0);
		}
		ft_free_array(tokens);
		node = node->next;
	}
	ft_lstclear(row_data, free);
	return (1);
}
