/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:17:04 by brivera           #+#    #+#             */
/*   Updated: 2024/10/10 15:40:48 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*ps;
	unsigned char			find;

	i = 0;
	ps = (const unsigned char *)s;
	find = (unsigned char)c;
	while (i < n)
	{
		if (ps[i] == find)
			return ((void *)&ps[i]);
		i++;
	}
	return (NULL);
}
