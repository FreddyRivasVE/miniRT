/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:40:13 by frivas            #+#    #+#             */
/*   Updated: 2025/08/21 13:10:24 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mrt_check_cy_details(char *ptr)
{
	double	cy_diameter;
	double	cy_height;

	if (!mrt_parse_vector(&ptr, -1000.0, 1000.0, false))
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1.0, 1.0, true))
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &cy_diameter))
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	if (cy_diameter <= 0)
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &cy_height))
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	if (cy_height <= 0)
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	mrt_skip_spaces(&ptr);
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
}

int	mrt_check_cy(char *cylinder)
{
	char	*ptr;

	ptr = cylinder;
	if (*ptr != 'c')
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	ptr++;
	if (*ptr != 'y')
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (ft_print_error("Error\nArgumentos errados! Cylinder"), 0);
	ptr++;
	mrt_skip_spaces(&ptr);
	return (mrt_check_cy_details(ptr));
}
