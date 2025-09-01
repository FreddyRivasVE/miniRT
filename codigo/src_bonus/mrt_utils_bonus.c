/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:00:00 by brivera           #+#    #+#             */
/*   Updated: 2025/09/01 15:13:11 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

bool	mrt_get_valid_t(float a, float b, float sqrt_disc, float *t_out)
{
	float	t1;
	float	t2;

	if (fabs(a) < EPSILON)
	{
		if (fabs(b) < EPSILON)
			return (false);
		*t_out = -sqrt_disc / b;
		return (*t_out > EPSILON);
	}
	t1 = (-b - sqrt_disc) / (2.0f * a);
	t2 = (-b + sqrt_disc) / (2.0f * a);
	if (t1 > EPSILON)
		*t_out = t1;
	else if (t2 > EPSILON)
		*t_out = t2;
	else
		return (false);
	return (true);
}
