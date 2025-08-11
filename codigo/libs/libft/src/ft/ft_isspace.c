/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:46:45 by frivas            #+#    #+#             */
/*   Updated: 2025/08/04 14:14:19 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *
 * \t (tab)  \n (LF)  \v (vertical tab)
 * \f (form feed)  \r (carriage return)
 * ' ' (espacio)
 * 
*/

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

char	*ft_strtrim_spaces(char *s)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (s[start] && ft_isspace(s[start]))
		start++;
	while (end > start && ft_isspace(s[end - 1]))
		end--;
	res = ft_substr(s, start, end - start);
	ft_free_ptr((void **)&s);
	return (res);
}
