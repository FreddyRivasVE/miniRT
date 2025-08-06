/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:34:00 by brivera           #+#    #+#             */
/*   Updated: 2025/08/06 09:26:20 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_push_object(t_scene_node **lst, t_type type, void *obj, t_vec4 rgb)
{
	t_scene_node	*new;
	t_scene_node	*last;

	if (!obj)
		return (0);
	new = ft_calloc(1, sizeof(t_scene_node));
	if (!new)
		return (0);
	new->type = type;
	new->object = obj;
	new->color = rgb;
	new->next = NULL;
	new->prev = NULL;
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
	return (1);
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

//L <x,y,z> <brightness> <R,G,B>
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

int	mrt_init_scene(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->camera = setup_test_camera();
	data->light = setup_test_light();
	data->ambient = setup_test_ambient();
	if (!data->camera || !data->ambient || !data->light)
		return (0);
	if (!mrt_push_object(&data->objects, SPHERE, setup_test_sphere(), vec4_create(1, 0, 0, 0)))
		return (0);
	if (!mrt_push_object(&data->objects, PLANE, setup_test_plane(), vec4_create(0.3, 0.5, 0.3, 0)))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_window	window;
	mlx_t		*mlx;
	t_data		elements;

	if (argc != 2)
		return (ft_print_error("Error\nFaltan argumentos. Ejemplo: ./miniRT file.rt"), 1);
	if (!mrt_read_file(argv[1]))
		return (1);
	if (!mrt_init_scene(&elements))
		return (ft_print_error("Error\nAl asignar memoria para t_data"), 1);
	window = mrt_setup_window(&mlx);
	mrt_draw_to_window(window, &elements);
	mlx_image_to_window(mlx, window.image, 0, 0);
	mlx_key_hook(mlx, &mrt_keyfuncion, mlx);
	mlx_loop(mlx);
	mrt_clear_scene(&elements);
	mlx_terminate(mlx);
	return (0);
}


