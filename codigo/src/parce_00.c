/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:16:28 by brivera           #+#    #+#             */
/*   Updated: 2025/07/28 18:23:18 by brivera          ###   ########.fr       */
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

int	mrt_read_file(char *file)
{
	char	*line;
	int		fd;

	if (!mrt_check_file_type(file))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error"), false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line); //borrar
		ft_free_ptr((void *)&line);
	}
	close(fd);
	return (true);
}
