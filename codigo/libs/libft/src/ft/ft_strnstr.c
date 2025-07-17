/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:22:14 by brivera           #+#    #+#             */
/*   Updated: 2024/10/11 15:54:23 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!str || !to_find) && !n)
		return (NULL);
	if (to_find[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < n)
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j] != '\0' && ((i + j) < n))
			j++;
		if (to_find[j] == '\0')
			return ((char *) &str[i]);
		i++;
	}
	return (NULL);
}
