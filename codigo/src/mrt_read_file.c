/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_read_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-08 14:18:57 by brivera           #+#    #+#             */
/*   Updated: 2025-08-08 14:18:57 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static int	mrt_ckeck_file(char *file)
{
	int fd;

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
	fd = mrt_ckeck_file(file);
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
		return (ft_print_error("Error\nArgumentos errados!"), NULL);
	return (close(fd), row_data);
}
