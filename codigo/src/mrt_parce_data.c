/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:16:28 by brivera           #+#    #+#             */
/*   Updated: 2025/08/10 10:21:34 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_validator_row_data(char *content)
{
	if (content[0] == 'A' && mrt_check_ambient(content))
		return (1);
	else if (content[0] == 'C' && mrt_check_camera(content))
		return (1);
	else if (content[0] == 'L' && mrt_check_light(content))
		return (1);
	else if (content[0] == 'p' && content [1] == 'l') //ojo falta el check
		return (1);
	else if (content[0] == 's' && content [1] == 'p' && mrt_check_sp(content))
		return (1);
	else if (content[0] == 'c' && content [1] == 'y') // ojo con el check
		return (1);
	else
		return (0);
}

int	mrt_read_row_data(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (!current)
		return (0);
	while (current)
	{
		if (!mrt_validator_row_data(current->content))
		{
			ft_lstclear(&lst, free);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
