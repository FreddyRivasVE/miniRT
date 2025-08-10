/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:24:54 by frivas            #+#    #+#             */
/*   Updated: 2025/08/10 10:52:58 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_pl(char *plane)
{
	char	*ptr;

	ptr = plane;
	if (*ptr != 'p')
		return (0);
	ptr++;
	if (*ptr != 'l')
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
	if (*ptr && mrt_check_rgb(&ptr))
		return (1);
	return (0);
}
