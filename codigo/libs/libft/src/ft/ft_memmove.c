/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:58:18 by brivera           #+#    #+#             */
/*   Updated: 2024/10/10 17:11:59 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	if (!src && !dest)
		return (NULL);
	pdest = (unsigned char *) dest;
	psrc = (const unsigned char *) src;
	if (pdest > psrc)
	{
		i = n;
		while (i > 0)
		{
			i--;
			pdest[i] = psrc[i];
		}
	}
	else
		ft_memcpy(pdest, psrc, n);
	return (dest);
}
