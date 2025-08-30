/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_init_scene_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:28:56 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 13:14:59 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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

int	mrt_dispatch_token(t_data *data, char **tokens)
{
	t_vec4	rgb;

	if (tokens[0][0] == 'A')
		return ((data->ambient = mrt_setup_ambient(tokens)) != NULL);
	if (tokens[0][0] == 'C')
		return ((data->camera = mrt_setup_camera(tokens)) != NULL);
	if (tokens[0][0] == 'L')
		return ((data->light = mrt_setup_light(tokens)) != NULL);
	if (tokens[0][0] == 's' && tokens[0][1] == 'p')
		return (mrt_push_object(&data->objects, SPHERE,
				mrt_setup_sphere(tokens, &rgb), rgb));
	if (tokens[0][0] == 'p' && tokens[0][1] == 'l')
		return (mrt_push_object(&data->objects, PLANE,
				mrt_setup_plane(tokens, &rgb), rgb));
	if (tokens[0][0] == 'c' && tokens[0][1] == 'y')
		return (mrt_push_object(&data->objects, CYLINDER,
				mrt_setup_cylinder(tokens, &rgb), rgb));
	return (0);
}

int	mrt_process_line(t_data *data, char *line)
{
	char	**tokens;
	int		result;

	tokens = ft_split_space(line);
	if (!tokens)
		return (0);
	result = mrt_dispatch_token(data, tokens);
	ft_free_array(tokens);
	return (result);
}

int	mrt_init_scene(t_data *data, t_list **row_data)
{
	t_list	*node;

	ft_memset(data, 0, sizeof(t_data));
	node = *row_data;
	while (node)
	{
		if (!mrt_process_line(data, node->content))
			return (ft_lstclear(row_data, free), 0);
		node = node->next;
	}
	ft_lstclear(row_data, free);
	return (1);
}
