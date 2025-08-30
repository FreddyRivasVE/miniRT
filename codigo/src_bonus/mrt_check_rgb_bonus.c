/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrt_check_rgb_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 11:54:52 by frivas            #+#    #+#             */
/*   Updated: 2025/08/30 13:14:41 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	mrt_extrac_rgb_data(char **arg, char *dest, int max_len)
{
	int	j;

	j = 0;
	while (**arg != '\0' && **arg != '\n' && j < max_len - 1)
	{
		if (ft_isdigit(**arg) || **arg == ',')
		{
			dest[j] = **arg;
			j++;
		}
		else
			break ;
		(*arg)++;
	}
	dest[j] = '\0';
	if (**arg != '\n' && **arg != '\0')
		return (0);
	return (j);
}

static int	mrt_comma_counter(const char *str)
{
	int	commas;

	commas = 0;
	while (*str != '\0')
	{
		if (*str == ',')
			commas++;
		str++;
	}
	return (commas);
}

static	int	mrt_parse_component(const char **str, int *value)
{
	*value = 0;
	if (!ft_isdigit(**str))
		return (0);
	while (ft_isdigit(**str))
	{
		*value = *value * 10 + (**str - '0');
		(*str)++;
	}
	return (*value >= 0 && *value <= 255);
}

static int	mrt_check_rgb_components(const char *str)
{
	const char	*ptr;
	int			counter;
	int			value;

	ptr = str;
	counter = 0;
	while (*ptr != '\0')
	{
		if (!mrt_parse_component(&ptr, &value))
			return (0);
		counter++;
		if (*ptr == ',')
			ptr++;
		else if (*ptr != '\0')
			return (0);
	}
	if (counter == 3)
		return (1);
	return (0);
}

int	mrt_check_rgb(char **ptr)
{
	char	buffer[20];

	if (mrt_extrac_rgb_data(ptr, buffer, sizeof(buffer)) == 0)
		return (0);
	if (mrt_comma_counter(buffer) != 2)
		return (0);
	if (!mrt_check_rgb_components(buffer))
		return (0);
	return (1);
}
