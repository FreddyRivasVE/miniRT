/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/08/05 21:07:28 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mrt_push_object(t_hittable_lst **lst, t_obj_type type, void *object, t_vec4 color)
{
	t_hittable_lst	*new;
	t_hittable_lst	*last;

	new = ft_calloc(1, sizeof(t_hittable_lst));
	if (!new)
		return ;
	new->type = type;
	new->object = object;
	new->color = color;
	new->next = NULL;
	new->prev = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

t_camera	*setup_test_camera()
{
	t_camera	*cam;

	cam = ft_calloc(1, sizeof(t_camera));
	if (!cam)
		return (NULL);
	cam->origin = vec4_create(0.0f, 0.0f, 0.0f, 1.0f);
	cam->direction = vec4_create(0.0f, 0.0f, -1.0f, 0.0f);
	cam->fov = 70.0f;
	return (cam);
}


t_point_light	*setup_test_light(void)
{
	t_point_light	*light;

	light = ft_calloc(1, sizeof(t_point_light));
	if (!light)
		return (NULL);
	*light = (t_point_light){
		.position = vec4_create(10, 10, 10, 1),
		.diff_color = vec4_create(1, 1, 1, 0),
		.diff_power = 0.9f,
		.spec_color = vec4_create(1, 1, 1, 0),
		.spec_power = 1.0f
	};
	return (light);
}

t_ambient	*setup_test_ambient(void)
{
	t_ambient	*amb;

	amb = ft_calloc(1, sizeof(t_ambient));
	if (!amb)
		return (NULL);
	amb->ratio = 0.1;
	amb->color = vec4_create(1, 1, 1, 0);
	return (amb);
}

t_sphere	*setup_test_sphere(void)
{
	t_sphere	*sp;

	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = vec4_create(0, 0, -3, 1);
	sp->radius = 1.0;
	return (sp);
}

t_plane	*setup_test_plane(void)
{
	t_plane	*pl;

	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->point = vec4_create(0, -1, 0, 1);
	pl->normal = vec4_create(0, 1, 0, 0);
	return (pl);
}


int	main(int argc, char **argv)
{
	t_window	window;
	mlx_t		*mlx;
	t_data		elements;

	if (argc != 2)
		return (ft_print_error("Error\nFaltan argumentos. Ejemplo: ./miniRT file.rt"), 1);
	if (!mrt_read_file(argv[1]))
		return (ft_print_error("Error\nNo se pudo leer el archivo"), 1);
	elements.camera = setup_test_camera();
	elements.light = setup_test_light();
	elements.ambient = setup_test_ambient();
	elements.objects = NULL;
	// Agregamos objetos 
	mrt_push_object(&elements.objects, SPHERE, setup_test_sphere(), vec4_create(1, 0, 0, 0));
	mrt_push_object(&elements.objects, PLANE, setup_test_plane(), vec4_create(0.3, 0.5, 0.3, 0));
	window = mrt_setup_window(&mlx);
	// Dibujamos
	mrt_draw_to_window(window, &elements);
	mlx_image_to_window(mlx, window.image, 0, 0);
	mlx_key_hook(mlx, &mrt_keyfuncion, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}


