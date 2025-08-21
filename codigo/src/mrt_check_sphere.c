/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:00:38 by frivas            #+#    #+#             */
/*   Updated: 2025/08/21 13:09:16 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_sp(char *sphere)
{
	char	*ptr;
	double	sph_diameter;

	ptr = sphere;
	if (*ptr != 's')
		return (ft_print_error("Error\nArgumentos errados! Sphere"), 0);
	ptr++;
	if (*ptr != 'p')
		return (ft_print_error("Error\nArgumentos errados! Sphere"), 0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (ft_print_error("Error\nArgumentos errados! Sphere"), 0);
	ptr++;
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1000.0, 1000.0, false))
		return (ft_print_error("Error\nArgumentos errados! Sphere"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &sph_diameter))
		return (ft_print_error("Error\nArgumentos errados! Sphere"), 0);
	if (sph_diameter <= 0)
		return (ft_print_error("Error\nArgumentos errados! Sphere"), 0);
	mrt_skip_spaces(&ptr);
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (ft_print_error("Error\nArgumentos errados! Sphere"), 0);
}
