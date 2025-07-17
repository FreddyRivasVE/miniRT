/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:30:26 by brivera           #+#    #+#             */
/*   Updated: 2024/10/10 15:43:15 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*ps1;
	unsigned const char	*ps2;
	size_t				i;

	i = 0;
	ps1 = (unsigned const char *)s1;
	ps2 = (unsigned const char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (ps1[i] != ps2[i])
			return ((int)(ps1[i] - ps2[i]));
		i++;
	}
	return (0);
}
