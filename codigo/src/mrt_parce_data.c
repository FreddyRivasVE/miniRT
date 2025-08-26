/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parce_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:16:28 by brivera           #+#    #+#             */
/*   Updated: 2025/08/26 14:02:30 by frivas           ###   ########.fr       */
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
	else if (content[0] == 'p' && content [1] == 'l' && mrt_check_pl(content))
		return (1);
	else if (content[0] == 's' && content [1] == 'p' && mrt_check_sp(content))
		return (1);
	else if (content[0] == 'c' && content [1] == 'y' && mrt_check_cy(content))
		return (1);
	else
		return (0);
}

bool	mrt_object_count(t_list *lst)
{
	int		count[3];
	t_list	*current;

	ft_memset(count, 0, sizeof(count));
	current = lst;
	if (!current)
		return (0);
	while (current)
	{
		if (((char *)current->content)[0] == 'A' && count[0] == 0)
			count[0] = 1;
		else if (((char *)current->content)[0] == 'C' && count[1] == 0)
			count[1] = 1;
		else if (((char *)current->content)[0] == 'L')
			count[2] = 1;
		current = current->next;
	}
	if (count[0] == 0 || count[1] == 0 || count[2] == 0)
		return (false);
	return (true);
}

int	mrt_read_row_data(t_list *lst)
{
	t_list	*current;

	if (!mrt_object_count(lst))
	{
		ft_print_error("Error\n Se requiere por lo menos una A, una L y una C");
		ft_lstclear(&lst, free);
		return (0);
	}
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
