/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 11:40:13 by frivas            #+#    #+#             */
/*   Updated: 2025/08/10 12:05:24 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mrt_check_cy_details(char *ptr)
{
	double	cy_diameter;
	double	cy_height;

	if (!mrt_parse_vector(&ptr, -1000.0, 1000.0))
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1.0, 1.0))
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &cy_diameter))
		return (0);
	if (cy_diameter <= 0)
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &cy_height))
		return (0);
	if (cy_height <= 0)
		return (0);
	mrt_skip_spaces(&ptr);
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (0);
}

int	mrt_check_cy(char *cylinder)
{
	char	*ptr;

	ptr = cylinder;
	if (*ptr != 'c')
		return (0);
	ptr++;
	if (*ptr != 'y')
		return (0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (0);
	ptr++;
	mrt_skip_spaces(&ptr);
	return (mrt_check_cy_details(ptr));
}
