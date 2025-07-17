/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:46:49 by brivera           #+#    #+#             */
/*   Updated: 2025/04/10 12:57:40 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countnewword(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	**ft_freestrs(char **strs, size_t j)
{
	while (j > 0)
	{
		free(strs[j - 1]);
		j--;
	}
	free(strs);
	return (NULL);
}

static char	**ft_fillstrs(char const *s, char c, char **strs)
{
	size_t	i;
	size_t	j;
	size_t	lenword;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		lenword = 0;
		if (s[i] != c)
		{
			while ((s[i + lenword] != '\0') && (s[i + lenword] != c))
				lenword++;
			strs[j] = ft_substr(s, i, lenword);
			if (strs[j] == NULL)
				return (strs = ft_freestrs(strs, j));
			j++;
			i = i + lenword;
		}
		else
			i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	size_t	newword;
	char	**strs;

	if (!s)
		return (NULL);
	newword = ft_countnewword(s, c);
	strs = (char **)malloc((newword + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	if (newword == 0)
	{
		strs[0] = NULL;
		return (strs);
	}
	strs = ft_fillstrs(s, c, strs);
	if (strs == NULL)
		return (NULL);
	return (strs);
}
