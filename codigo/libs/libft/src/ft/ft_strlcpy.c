/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:41:31 by brivera           #+#    #+#             */
/*   Updated: 2024/09/25 10:15:04 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	counter;

	counter = 0;
	while (src[counter] != '\0')
	{
		counter++;
	}
	if (size == 0)
		return (counter);
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (counter);
}
