/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_cone_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:33:01 by frivas            #+#    #+#             */
/*   Updated: 2025/08/30 16:08:47 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	mrt_check_cn_details(char *ptr)
{
	double	cn_diameter;
	double	cn_height;

	if (!mrt_parse_vector(&ptr, -1000.0, 1000.0, false))
		return (ft_print_error("Error\nRevisa datos de posicion Cone"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1.0, 1.0, true))
		return (ft_print_error("Error\nRevisa valores de normal Cone"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &cn_diameter))
		return (ft_print_error("Error\nRevisa valores diametro Cone"), 0);
	if (cn_diameter <= 0)
		return (ft_print_error("Error\nRevisa valores diametro Cone"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &cn_height))
		return (ft_print_error("Error\nRevisa valores altura Cone"), 0);
	if (cn_height <= 0)
		return (ft_print_error("Error\nRevisa valores altura Cone"), 0);
	mrt_skip_spaces(&ptr);
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (ft_print_error("Error\nRevisa valores de RGB de Cone"), 0);
}

int	mrt_check_cn(char *cone)
{
	char	*ptr;

	ptr = cone;
	if (*ptr != 'c')
		return (ft_print_error("Error\nRevisa argumentos de Cone"), 0);
	ptr++;
	if (*ptr != 'n')
		return (ft_print_error("Error\nRevisa argumentos de Cone"), 0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (ft_print_error("Error\nRevisa espaciado de Cone"), 0);
	ptr++;
	mrt_skip_spaces(&ptr);
	return (mrt_check_cn_details(ptr));
}
