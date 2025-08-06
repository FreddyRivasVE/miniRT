/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:40:57 by frivas            #+#    #+#             */
/*   Updated: 2025/08/06 10:57:49 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mrt_check_ambient(char *amb_light)
{
	int	i;

	i = 1;
	if (amb_light[i] && !ft_isspace(amb_light[i]))
		return (0);
	while (amb_light[i] && ft_isspace(amb_light[i]))
		i++;
	if (amb_light[i] && !ft_isdigit(amb_light[i]))
		return (0);
	if (amb_light[i] && amb_light[i] != '0' && amb_light[i] != 1)
		return (0);
	i++;
	if (amb_light[i] && amb_light[i] != '.')
		return (0);
	i++;
	if (amb_light[i] && !ft_isdigit(amb_light[i]))
		return (0);
	i++;
	while (amb_light[i] && ft_isspace(amb_light[i]))
		i++;
	if (amb_light[i] && mrt_check_rgb(i, amb_light))
		return (1);
	else
		return (0);
}
