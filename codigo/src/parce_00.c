/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:16:28 by brivera           #+#    #+#             */
/*   Updated: 2025/08/07 13:21:15 by frivas           ###   ########.fr       */
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

int	mrt_upload_row_data(char *line, t_row_data *r_data)
{
	if (line[0] == '\n')
		return (1);
	if (line[0] == 'A' && !r_data->r_amb_light)
		r_data->r_amb_light = ft_strdup(line);
	else if (line[0] == 'C' && !r_data->r_camera)
		r_data->r_camera = ft_strdup(line);
	else if (line[0] == 'L' && !r_data->r_light)
		r_data->r_light = ft_strdup(line);
	else if (line[0] == 'p' && line [1] == 'l' && !r_data->r_plane)
		r_data->r_plane = ft_strdup(line);
	else if (line[0] == 's' && line [1] == 'p' && !r_data->r_sphere)
		r_data->r_sphere = ft_strdup(line);
	else if (line[0] == 'c' && line [1] == 'y' && !r_data->r_cylinder)
		r_data->r_cylinder = ft_strdup(line);
	else
		return (0);
	return (1);
}

int	mrt_check_row_data(t_row_data *r_data)
{
	if (!mrt_check_ambient(r_data->r_amb_light))
		return (0);
	if (!mrt_check_camera(r_data->r_camera))
		return (0);
	if (!mrt_check_light(r_data->r_light))
		return (0);
	if (!mrt_check_sphere(r_data->r_sphere))
		return (0);
	return (1);
}

int	mrt_read_file(char *file)
{
	t_row_data	r_data;
	char		*line;
	int			fd;

	r_data.r_amb_light = NULL;
	r_data.r_camera = NULL;
	r_data.r_light = NULL;
	r_data.r_plane = NULL;
	r_data.r_plane = NULL;
	r_data.r_sphere = NULL;
	r_data.r_cylinder = NULL;
	if (!mrt_check_file_type(file))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n No se puede abrir el archivo"), false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (mrt_upload_row_data(line, &r_data) == 0)
			return (ft_print_error("Error\n Argumentos errados!"), false);
		ft_free_ptr((void *)&line);
	}
	if (!r_data.r_amb_light || !r_data.r_camera || !r_data.r_light)
		return (ft_print_error("Error\n Argumentos errados!"), false);
	if (mrt_check_row_data(&r_data) == 0)
		return (ft_print_error("Error\n Argumentos errados!"), false);
	close(fd);
	return (true);
}
