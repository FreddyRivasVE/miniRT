/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:18:57 by brivera           #+#    #+#             */
/*   Updated: 2025/08/21 13:03:19 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mrt_upload_row_data(char *line, t_list **row_data)
{
	t_list	*new_node;
	char	*content;

	if (!ft_strcmp(line, "\n") || line[0] == '#')
		return (1);
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

static int	mrt_check_file_type(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		return (ft_print_error("Error\n Solo archivos .rt"), false);
	if (ft_strncmp(&file[len - 3], ".rt", 3))
		return (ft_print_error("Error\nSolo archivos .rt"), false);
	return (true);
}

static int	mrt_check_file(char *file)
{
	int	fd;

	if (!mrt_check_file_type(file))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nArchivo"), false);
	return (fd);
}

t_list	*mrt_read_file(char *file)
{
	t_list		*row_data;
	char		*content;
	int			fd;
	bool		flag;

	row_data = NULL;
	fd = mrt_check_file(file);
	if (fd == 0)
		return (NULL);
	flag = false;
	while (1)
	{
		content = get_next_line(fd);
		if (!content)
			break ;
		if (!mrt_upload_row_data(content, &row_data) && !flag)
		{
			ft_print_error("Error\nAl asignar memoria");
			flag = true;
		}
		ft_free_ptr((void *)&content);
	}
	if (!mrt_read_row_data(row_data))
		return (NULL);
	return (close(fd), row_data);
}
