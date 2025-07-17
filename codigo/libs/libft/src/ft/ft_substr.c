/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:22:11 by brivera           #+#    #+#             */
/*   Updated: 2024/09/30 11:00:22 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int		i;
	char				*substring;
	size_t				len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_calloc(1, sizeof(char)));
	if (start + len > len_s)
		len = len_s - start;
	substring = (char *)malloc(len + 1);
	if (substring == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
