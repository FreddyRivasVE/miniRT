/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:03:15 by brivera           #+#    #+#             */
/*   Updated: 2024/10/11 15:36:01 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*newstrs;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	newstrs = (char *)malloc(len + 1);
	if (newstrs == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		newstrs[i] = f(i, s[i]);
		i++;
	}
	newstrs[len] = '\0';
	return (newstrs);
}
