/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_ambient.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:40:57 by frivas            #+#    #+#             */
/*   Updated: 2025/08/29 11:11:45 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_ambient(char *amb_light)
{
	char	*ptr;
	double	alr;

	ptr = amb_light;
	if (*ptr != 'A')
		return (ft_print_error("Error\nRevisa Argumentos de Ambient "), 0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (ft_print_error("Error\nRevisa espacios de Ambient"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &alr))
		return (ft_print_error("Error\nRevisa el ratio de luz Ambient"), 0);
	if (!mrt_is_view_in_range(alr, 0.0, 1.0))
		return (ft_print_error("Error\nRevisa el ratio de luz Ambient"), 0);
	mrt_skip_spaces(&ptr);
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (ft_print_error("Error\nRevisa los valores RGB de Ambient"), 0);
}
