/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parce_data_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:16:28 by brivera           #+#    #+#             */
/*   Updated: 2025/09/02 13:26:56 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	mrt_validator_row_data(char *content)
{
	if (content[0] == 'A')
		return (mrt_check_ambient(content));
	else if (content[0] == 'C')
		return (mrt_check_camera(content));
	else if (content[0] == 'L')
		return (mrt_check_light(content));
	else if (content[0] == 'p' && content[1] == 'l')
		return (mrt_check_pl(content));
	else if (content[0] == 's' && content[1] == 'p')
		return (mrt_check_sp(content));
	else if (content[0] == 'c' && content[1] == 'y')
		return (mrt_check_cy(content));
	else if (content[0] == 'c' && content[1] == 'n')
		return (mrt_check_cn(content));
	return (3);
}

static bool	mrt_validate_and_count(t_list *lst, int *count)
{
	t_list	*current;
	int		flag;

	ft_memset(count, 0, 3 * sizeof(int));
	current = lst;
	flag = 0;
	while (current)
	{
		flag = mrt_validator_row_data(current->content);
		if (flag == 3)
			return (ft_print_error("Error\nRevisa argumentos."), false);
		if (flag == 0)
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
