/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:51:10 by frivas            #+#    #+#             */
/*   Updated: 2025/08/06 13:48:51 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mrt_skip_spaces(char **str)
{
	while (**str && ft_isspace(**str))
		(*str)++;
}

int	mrt_is_view_in_range(double val, double min, double max)
{
	return (val >= min && val <= max);
}

int	mrt_parse_vector(char **str, double min, double max)
{
	int		i;
	double	val;

	i = 0;
	while (i < 3)
	{
		if (!mrt_parse_float(str, &val))
			return (0);
		if (!mrt_is_view_in_range(val, min, max))
			return (0);
		if (i < 2)
		{
			if (**str != ',')
				return (0);
			(*str)++;
		}
		i++;
	}
	return (1);
}

int	mrt_check_camera(char *camera)
{
	char	*ptr;
	double	fov;

	ptr = camera;
	if (*ptr != 'C')
		return (0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (0);
	ptr++;
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1000.0, 1000.0))
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1.0, 1.0))
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &fov))
		return (0);
	if (!mrt_is_view_in_range(fov, 0.0, 180.0))
		return (0);
	if (*ptr != '\n' && *ptr != '\0')
		return (0);
	return (1);
}
