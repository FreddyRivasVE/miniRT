/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_parse_float_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:49:53 by frivas            #+#    #+#             */
/*   Updated: 2025/08/30 13:15:11 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	mrt_parse_sign(char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	if (**str == '+')
		(*str)++;
	return (1);
}

static int	mrt_parse_integer_part(char **str, double *result)
{
	int	has_digits;

	has_digits = 0;
	while (ft_isdigit(**str))
	{
		has_digits = 1;
		*result = *result * 10 + (**str - '0');
		(*str)++;
	}
	return (has_digits);
}

static void	mrt_parse_fractional_part(char **str, double *result)
{
	double	frac;
	double	div;

	frac = 0.0;
	div = 10.0;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			frac += (**str - '0') / div;
			div *= 10.0;
			(*str)++;
		}
		*result += frac;
	}
}

int	mrt_parse_float(char **str, double *out)
{
	double	result;
	int		sign;
	int		has_digits;

	result = 0.0;
	sign = mrt_parse_sign(str);
	has_digits = mrt_parse_integer_part(str, &result);
	mrt_parse_fractional_part(str, &result);
	if (!has_digits)
		return (0);
	*out = result * sign;
	return (1);
}
