/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_extrac_data_elements.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:13:23 by frivas            #+#    #+#             */
/*   Updated: 2025/08/10 17:50:39 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4 mrt_extrac_color(const char *str)
{
	t_vec4	color;
	char	*end;
	int		r;
	int		g;
	int		b;

	r = ft_atoi(str);
	end = ft_strchr(str, ',');
	if (!end)
		return (vec4_create(0, 0, 0, 0));
	g = ft_atoi(end + 1);
	end = ft_strchr(end + 1, ',');
	if (!end)
		return (vec4_create(0, 0, 0, 0));
	b = ft_atoi(end + 1);
	color[0] = r / 255.0f;
	color[1] = g / 255.0f;
	color[2] = b / 255.0f;
	color[3] = 0.0f;
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
