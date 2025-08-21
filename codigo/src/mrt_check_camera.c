/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:51:10 by frivas            #+#    #+#             */
/*   Updated: 2025/08/21 22:29:20 by frivas           ###   ########.fr       */
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

int	mrt_parse_vector_raw(char **str, double min, double max, double out[3])
{
	double	val;

	if (!mrt_parse_float(str, &val))
		return (0);
	if (!mrt_is_view_in_range(val, min, max))
		return (0);
	out[0] = val;
	if (**str != ',')
		return (0);
	(*str)++;
	if (!mrt_parse_float(str, &val))
		return (0);
	if (!mrt_is_view_in_range(val, min, max))
		return (0);
	out[1] = val;
	if (**str != ',')
		return (0);
	(*str)++;
	if (!mrt_parse_float(str, &val))
		return (0);
	if (!mrt_is_view_in_range(val, min, max))
		return (0);
	out[2] = val;
	return (1);
}

int	mrt_parse_vector(char **str, double min, double max, int flag)
{
	double	v[3];
	double	len;

	if (!mrt_parse_vector_raw(str, min, max, v))
		return (0);
	if (flag)
	{
		len = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
		if (fabs(len - 1.0) > EPSILON)
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
