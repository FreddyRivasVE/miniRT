/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 15:17:40 by frivas            #+#    #+#             */
/*   Updated: 2025/08/06 23:45:38 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_light(char *light)
{
	char	*ptr;
	double	lbrig;

	ptr = light;
	if (*ptr != 'L')
		return (0);
	ptr++;
	if (!ft_isspace(*ptr))
		return (0);
	ptr++;
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_vector(&ptr, -1000.0, 1000.0))
		return (0);
	mrt_skip_spaces(&ptr);
	if (!mrt_parse_float(&ptr, &lbrig))
		return (0);
	if (!mrt_is_view_in_range(lbrig, 0.0, 1.0))
		return (0);
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (0);
}
