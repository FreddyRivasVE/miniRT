/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_ambient.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:40:57 by frivas            #+#    #+#             */
/*   Updated: 2025/08/19 22:44:50 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_ambient(char *amb_light)
{
	char	*ptr;
	double	alr;

	ptr = amb_light;
	if (*ptr != 'A')
		return (0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &alr))
		return (0);
	if (!mrt_is_view_in_range(alr, 0.0, 1.0))
		return (0);
	mrt_skip_spaces(&ptr);
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (0);
}
