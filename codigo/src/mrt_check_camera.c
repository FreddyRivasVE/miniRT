/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:51:10 by frivas            #+#    #+#             */
/*   Updated: 2025/08/21 14:07:29 by frivas           ###   ########.fr       */
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

int	mrt_parse_vector(char **str, double min, double max, int flag)
{
	int		i;
	double	val;
	double	x;
	double	y;
	double	z;

	i = 0;
	while (i < 3)
	{
		if (!mrt_parse_float(str, &val))
			return (0);
		if (flag)
		{
			if (i == 0)
				x = val;
			else if (i == 1)
				y = val;
			else
				z = val;
		}
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
	if (flag)
	{
		if (fabs(sqrt((x * x) + (y * y) + (z * z)) - 1.0) > EPSILON)
			return (0);
	}
	return (1);
}

int	mrt_check_camera(char *camera)
{
	char	*ptr;
	double	fov;

	ptr = camera;
	if (*ptr != 'C')
		return (ft_print_error("Error\nArgumentos errados! Camera"), 0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (ft_print_error("Error\nArgumentos errados! Camera"), 0);
	ptr++;
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1000.0, 1000.0, false))
		return (ft_print_error("Error\nArgumentos errados! Camera"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1.0, 1.0, true))
		return (ft_print_error("Error\nArgumentos errados! Camera"), 0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &fov))
		return (ft_print_error("Error\nArgumentos errados! Camera"), 0);
	if (!mrt_is_view_in_range(fov, 0.0, 180.0))
		return (ft_print_error("Error\nArgumentos errados! Camera"), 0);
	if (*ptr != '\n' && *ptr != '\0')
		return (ft_print_error("Error\nArgumentos errados! Camera"), 0);
	return (1);
}
