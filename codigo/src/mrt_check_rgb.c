/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:54:52 by frivas            #+#    #+#             */
/*   Updated: 2025/08/05 12:53:48 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	mrt_extrac_rgb_data(int i, const char *arg, char *dest, int max_len)
{
	int	j;
	int	k;

	j = 0;
	k = i;
	while (arg[k] != '\0' && j < max_len - 1)
	{
		if (ft_isdigit(arg[k]) || arg[k] == ',')
		{
			dest[j] = arg[k];
			j++;
		}
		else
			break ;
		k++;
	}
	dest[j] = '\0';
	return (j);
}

static int	mrt_comma_counter(const char *str)
{
	int	i;
	int	commas;

	i = 0;
	commas = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	return (commas);
}

static int	check_rgb_components(const char *str)
{
	int	i;
	int	counter;
	int	value;

	i = 0;
	counter = 0;
	value = 0;

	while (str[i] != '\0')
	{
		value = 0;
		while (ft_isdigit(str[i]))
		{
			value = value * 10 + (str[i] - '0');
			i++;
		}
		if (value < 0 || value > 255)
			return (0);
		counter++;
		if (str[i] == ',')
			i++;
		else if (str[i] != '\0')
			return (0);
	}
	if (counter == 3)
		return (1);
	return (0);
}

int	mrt_check_rgb(int i, const char *arg)
{
	char	buffer[20];

	if (mrt_extrac_rgb_data(i, arg, buffer, sizeof(buffer)) == 0)
		return (0);
	if (mrt_comma_counter(buffer) != 2)
		return (0);
	if (!check_rgb_components(buffer))
		return (0);
	return (1);
}
