/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_free_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-06 13:27:33 by brivera           #+#    #+#             */
/*   Updated: 2025-08-06 13:27:33 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void    mrt_free_scene_nodes(t_scene_node **lst)
{
	t_scene_node *current;
	t_scene_node *next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_free_ptr((void **)&current->object);
		ft_free_ptr((void **)&current);
		current = next;
	}
	*lst = NULL;
}

void	mrt_clear_scene(t_data *element)
{
	ft_free_ptr((void **)&element->camera);
	ft_free_ptr((void **)&element->light);
	ft_free_ptr((void **)&element->ambient);
	mrt_free_scene_nodes(&element->objects);
}
