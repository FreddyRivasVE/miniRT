/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_init_scene_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:59:10 by brivera           #+#    #+#             */
/*   Updated: 2025/08/10 18:27:16 by frivas           ###   ########.fr       */
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
	if (!*lst)
	{
		*lst = new;
		return (1);
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	return (1);
}

/*
 * Funcion para cargar la estrucutura pincipal
 * aca deberia llegar lo del parce
 * pude haber dos esferas, aspecto que ahora no se tienen en cuenta
 * todo se caga en una lista 
 * ya esta la funcion de free lista
 * asi que al menos aca no deberian salir leeks
 * 
*/

// int	mrt_init_scene(t_data *data, t_list **file)
// {
// 	t_sphere	*sp1;
// 	t_sphere	*sp2;
// 	t_vec4		sp1_rgb;
// 	t_vec4		sp2_rgb;

// 	ft_memset(data, 0, sizeof(t_data));
// 	data->camera = setup_test_camera();
// 	data->light = setup_test_light();
// 	data->ambient = setup_test_ambient();
// 	if (!data->camera || !data->ambient || !data->light)
// 		return (0);
// 	sp1 = setup_test_sphere(vec4_create(0.0f, 0.0f, -3.0f, 1.0f), (float)1.0);
// 	sp1_rgb = vec4_create(1, 0, 0, 0);
// 	sp2 = setup_test_sphere(vec4_create(2.0f, 0.0f, -4.0f, 1.0f), (float)1.0);
// 	sp2_rgb = vec4_create(0.3, 0.5, 0.3, 0);
// 	if (!mrt_push_object(&data->objects, SPHERE, sp1, sp1_rgb))
// 		return (0);
// 	if (!mrt_push_object(&data->objects, SPHERE, sp2, sp2_rgb))
// 		return (0);
//     ft_lstclear(file, free);
// 	return (1);
// }

int	mrt_init_scene(t_data *data, t_list **row_data)
{
	t_sphere	*sp1; //ir borrando
	t_sphere	*sp2; //ir borrando
	t_vec4		sp1_rgb; //ir borrando
	t_vec4		sp2_rgb; //ir borrando
	t_list	*node;
	char	**tokens;
	
	node = *row_data;
	ft_memset(data, 0, sizeof(t_data));
//	data->light = setup_test_light(); //ir borrando
	while (node)
	{
		tokens = ft_split(node->content, ' ');
		if (!tokens)
			return (0);
		if (tokens[0][0] == 'A')
		{
			data->ambient = mrt_setup_ambient(tokens);
			if (!data->ambient)
				return (0);
		}
		else if(tokens[0][0] == 'C')
		{
			data->camera = mrt_setup_camera(tokens);
			if (!data->camera)
				return (0);
		}
		else if(tokens[0][0] == 'L')
		{
			data->light = mrt_setup_light(tokens);
			if (!data->light)
				return (0);
		}
		ft_free_array(tokens);
		node = node->next;
	}
	ft_lstclear(row_data, free);
	if (!data->camera || !data->ambient || !data->light) //ir borrando
		return (0); //ir borrando
	sp1 = setup_test_sphere(vec4_create(0.0f, 0.0f, -3.0f, 1.0f), (float)1.0); //ir borrando
	sp1_rgb = vec4_create(1, 0, 0, 0); //ir borrando
	sp2 = setup_test_sphere(vec4_create(2.0f, 0.0f, -4.0f, 1.0f), (float)1.0); //ir borrando
	sp2_rgb = vec4_create(0.3, 0.5, 0.3, 0); //ir borrando
	if (!mrt_push_object(&data->objects, SPHERE, sp1, sp1_rgb)) //ir borrando
		return (0); //ir borrando
	if (!mrt_push_object(&data->objects, SPHERE, sp2, sp2_rgb)) //ir borrando
		return (0); //ir borrando
	return (1);
}
