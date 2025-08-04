/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:40:57 by frivas            #+#    #+#             */
/*   Updated: 2025/08/04 14:25:08 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_ambient(t_row_data *r_data)
{
	int	i;

	i = 1;
	if (r_data->r_amb_light[i] && !ft_isspace(r_data->r_amb_light[i]))
		return (0);
	while (r_data->r_amb_light[i] && ft_isspace(r_data->r_amb_light[i]))
		i++;
	if (r_data->r_amb_light[i] && !ft_isdigit(r_data->r_amb_light[i]))
		return (0);
	if (r_data->r_amb_light[i] && r_data->r_amb_light[i] != '0'
		&& r_data->r_amb_light[i] != 1)
		return (0);
	i++;
	if (r_data->r_amb_light[i] && r_data->r_amb_light[i] != '.')
		return (0);
	i++;
	if (r_data->r_amb_light[i] && !ft_isdigit(r_data->r_amb_light[i]))
		return (0);
	i++;
	while (r_data->r_amb_light[i] && ft_isspace(r_data->r_amb_light[i]))
		i++;
	if (r_data->r_amb_light[i] && mrt_check_rgb(i, r_data))
		return (1);
	else
		return (0);
}
