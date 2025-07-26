/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/07/26 19:21:05 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_window	mrt_setup_window(mlx_t **mlx)
{
	t_window	window;

	window.width = WIDTH;
	window.height = (int)(window.width / ASPECT_RATIO);
	*mlx = mlx_init(window.width, window.height, "miniRT", true);
	window.image = mlx_new_image(*mlx, window.width, window.height);
	return (window);
}

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

int	main(int argc, char **argv)
{
	t_window	window;
	mlx_t		*mlx;

	if (argc != 2)
		return (ft_print_error("Error\nFaltan argumentos!.Ejemplo:./miniRT file.rt"), 1);
	if (!mrt_read_file(argv[1]))
		return (1);
	window = mrt_setup_window(&mlx);
	mlx_image_to_window(mlx, window.image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
