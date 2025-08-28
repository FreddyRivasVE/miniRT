/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:19:05 by brivera           #+#    #+#             */
/*   Updated: 2025/08/28 15:37:10 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (count);
}

static char	**ft_fillstrs(char const *s, char **strs)
{
	size_t	i;
	size_t	j;
	size_t	lenword;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			lenword = 0;
			while (s[i + lenword] && !ft_isspace(s[i + lenword]))
				lenword++;
			strs[j] = ft_substr(s, i, lenword);
			if (!strs[j])
				return (ft_free_array(strs), NULL);
			j++;
			i += lenword;
		}
	}
	return (strs);
}

char	**ft_split_space(char const *s)
{
	size_t	word;
	char	**strs;

	if (!s)
		return (NULL);
	word = ft_count(s);
	strs = (char **)ft_calloc(word + 1, sizeof(char *));
	if (!strs)
		return (NULL);
	if (word == 0)
		return (strs);
	if (!ft_fillstrs(s, strs))
		return (NULL);
	return (strs);
}
