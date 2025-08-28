/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parce_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:16:28 by brivera           #+#    #+#             */
/*   Updated: 2025/08/28 16:30:30 by brivera          ###   ########.fr       */
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

static bool	mrt_validate_and_count(t_list *lst, int *count)
{
	t_list	*current;

	ft_memset(count, 0, 3 * sizeof(int));
	current = lst;
	while (current)
	{
		if (!mrt_validator_row_data(current->content))
			return (false);
		if (((char *)current->content)[0] == 'A')
			count[0]++;
		else if (((char *)current->content)[0] == 'C')
			count[1]++;
		else if (((char *)current->content)[0] == 'L')
			count[2]++;
		current = current->next;
	}
	return (true);
}

static bool	mrt_check_mandatory_elements(int *count)
{
	if (count[0] != 1)
	{
		ft_print_error("Error\nDebe haber exactamente un ambiente (A)");
		return (false);
	}
	if (count[1] != 1)
	{
		ft_print_error("Error\nDebe haber exactamente una cámara (C)");
		return (false);
	}
	if (count[2] < 1)
	{
		ft_print_error("Error\nDebe haber al menos una luz (L)");
		return (false);
	}
	return (true);
}

int	mrt_read_row_data(t_list *lst)
{
	int	count[3];

	if (!lst)
	{
		ft_print_error("Error\nArchivo vacío o sin contenido válido");
		return (0);
	}
	if (!mrt_validate_and_count(lst, count))
	{
		ft_lstclear(&lst, free);
		return (0);
	}
	if (!mrt_check_mandatory_elements(count))
	{
		ft_lstclear(&lst, free);
		return (0);
	}
	return (1);
}
