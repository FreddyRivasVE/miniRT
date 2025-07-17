/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:05:43 by brivera           #+#    #+#             */
/*   Updated: 2024/10/10 15:57:30 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	if ((dest == NULL) && (src == NULL))
		return (NULL);
	i = 0;
	pdest = (unsigned char *)dest;
	psrc = (const unsigned char *)src;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}
