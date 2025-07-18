/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-18 09:44:26 by brivera           #+#    #+#             */
/*   Updated: 2025-07-18 09:44:26 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Compares two strings.
Returns 0 if `s1` and `s2` are equal.
Returns <0 if `s1` is less than `s2` (in ASCII order).
Returns >0 if `s1` is greater than `s2`.
Note: Uses `unsigned char` to correctly handle values >127.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
Its purpose is to count the number of consecutive characters 
at the beginning of the string `s` that are present in the string `accept`.
*/
size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break ;
		++i;
	}
	return (i);
}

/*
The function scans the string `s` looking for
the first character that is present in `reject`.
*/
size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (reject[k] != '\0')
		{
			if (s[i] == reject[k])
				return (i);
			k++;
		}
		k = 0;
		i++;
	}
	return (i);
}

/*
Searches for the last occurrence of the character `c` in the string `str`.
Returns its index, or -1 if not found.
*/
size_t	ft_seek_lastc(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] && i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (i);
}
