/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:47:50 by frivas            #+#    #+#             */
/*   Updated: 2025/08/10 16:10:34 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	mrt_fractional_part(const char *str, int *i)
{
	float	frac;
	float	div;

	frac = 0.0f;
	div = 10.0f;
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			frac += (str[*i] - '0') / div;
			div *= 10.0f;
			(*i)++;
		}
	}
	return (frac);
}

float	ft_atof(const char *str)
{
	float	num;
	float	frac;
	int	sig;
	int	i;

	num = 0.0f;
	frac = 0.0f;
	sig = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10.0f + (str[i] - '0');
		i++;
	}
	frac = mrt_fractional_part(str, &i);
	return (sig * (num + frac));
}
