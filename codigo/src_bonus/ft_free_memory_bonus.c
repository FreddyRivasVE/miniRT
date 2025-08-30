/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 10:59:45 by brivera           #+#    #+#             */
/*   Updated: 2025/08/30 13:14:05 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	mrt_free_scene_nodes(t_scene_node **lst)
{
	t_scene_node	*current;
	t_scene_node	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_free_ptr((void **)&current->hit->material);
		ft_free_ptr((void **)&current->hit);
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
