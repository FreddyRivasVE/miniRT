/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/07/24 17:46:37 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_print_error(char *msj)
{
	ft_putendl_fd(msj, 2);
}

int	mrt_check_file_type(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 3)
		return (ft_print_error("Example: ./miniRT file.rt"), false);
	if (ft_strncmp(&file[len - 3], ".rt", 3))
		return (ft_print_error("Example: ./miniRT file.rt"), false);
	return (true);
}

int	mrt_read_file(char *file)
{
	//char	*line;
	int		fd;

	if (!mrt_check_file_type(file))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("Error"), false);
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_print_error("Example: ./miniRT file.rt"), 1);
	if (!mrt_read_file(argv[1]))
		return (1);
	return (0);
}
