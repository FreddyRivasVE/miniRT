/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:17:40 by frivas            #+#    #+#             */
/*   Updated: 2025/08/21 22:56:29 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		return (0);
	ptr++;
	if (!mrt_light_fail(ft_isspace(*ptr)))
		return (0);
	ptr++;
	mrt_skip_spaces(&ptr);
	if (!mrt_light_fail(mrt_parse_vector(&ptr, -1000.0, 1000.0, false)))
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_light_fail(mrt_parse_float(&ptr, &lbrig)))
		return (0);
	if (!mrt_light_fail(mrt_is_view_in_range(lbrig, 0.0, 1.0)))
		return (0);
	if (*ptr && *ptr != '\n')
	{
		mrt_skip_spaces(&ptr);
		if (!mrt_light_fail(*ptr && mrt_check_rgb(&ptr)))
			return (0);
	}
	return (1);
}
