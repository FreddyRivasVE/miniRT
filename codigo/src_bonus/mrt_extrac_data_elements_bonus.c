/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_extrac_data_elements_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:13:23 by frivas            #+#    #+#             */
/*   Updated: 2025/08/30 13:14:47 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec4	mrt_extract_color(const char *str)
{
	char	**rgb;
	t_vec4	color;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (vec4_create(0, 0, 0, 0));
	color = vec4_create(
			ft_atof(rgb[0]) / 255.0f,
			ft_atof(rgb[1]) / 255.0f,
			ft_atof(rgb[2]) / 255.0f,
			0);
	ft_free_array(rgb);
	return (color);
}

t_vec4	mrt_extrac_vector(const char *str, float w)
{
	t_vec4	res;
	char	*end;

	res[0] = ft_atof(str);
	end = ft_strchr(str, ',');
	if (!end)
		return (vec4_create(0, 0, 0, w));
	res[1] = ft_atof(end + 1);
	end = ft_strchr(end + 1, ',');
	if (!end)
		return (vec4_create(0, 0, 0, w));
	res[2] = ft_atof(end + 1);
	res[3] = w;
	return (res);
}
