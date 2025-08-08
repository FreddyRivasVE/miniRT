/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:16:28 by brivera           #+#    #+#             */
/*   Updated: 2025/08/08 15:11:51 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_file_type(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		return (ft_print_error("Error\nExample: ./miniRT file.rt"), false);
	if (ft_strncmp(&file[len - 3], ".rt", 3))
		return (ft_print_error("Error\nExample: ./miniRT file.rt"), false);
	return (true);
}

int	mrt_upload_row_data(char *line, t_list **row_data)
{
	t_list	*new_node;
	char	*content;

	content = ft_strdup(line);
	if (!content)
		return (0);
	new_node = ft_lstnew(content);
	if (!new_node)
	{
		ft_lstclear(row_data, free);
		return (0);
	}
	ft_lstadd_back(row_data, new_node);
	return (1);
}

int	mrt_validator_row_data(char *content)
{
	if (content[0] == '\n')
		return (1);
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
		return (printf("hola4\n"), 0);
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
