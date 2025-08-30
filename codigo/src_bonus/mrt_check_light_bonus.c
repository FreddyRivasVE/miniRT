/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_light_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:17:40 by frivas            #+#    #+#             */
/*   Updated: 2025/08/30 13:14:35 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	mrt_light_fail(int cond)
{
	if (!cond)
	{
		ft_print_error("Error\nArgumentos errados! Light");
		return (0);
	}
	return (1);
}

int	mrt_check_light(char *light)
{
	char	*ptr;
	double	lbrig;

	ptr = light;
	if (!mrt_light_fail(*ptr == 'L'))
		return (ft_print_error("Error\nRevisa argumentos de Light"), 0);
	ptr++;
	if (!mrt_light_fail(ft_isspace(*ptr)))
		return (ft_print_error("Error\nRevisa espaciado de Light"), 0);
	ptr++;
	mrt_skip_spaces(&ptr);
	if (!mrt_light_fail(mrt_parse_vector(&ptr, -1000.0, 1000.0, false)))
		return (ft_print_error("Error\nRevisa datos de posicion Light"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_light_fail(mrt_parse_float(&ptr, &lbrig)))
		return (ft_print_error("Error\nRevisa el ratio de luz de Light"), 0);
	if (!mrt_light_fail(mrt_is_view_in_range(lbrig, 0.0, 1.0)))
		return (ft_print_error("Error\nRevisa el ratio de luz de Light"), 0);
	if (*ptr && *ptr != '\n')
	{
		mrt_skip_spaces(&ptr);
		if (!mrt_light_fail(*ptr && mrt_check_rgb(&ptr)))
			return (ft_print_error("Error\nRevisa valores RGB de Light"), 0);
	}
	return (1);
}
