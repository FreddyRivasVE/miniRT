/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:15:39 by brivera           #+#    #+#             */
/*   Updated: 2025/04/25 17:00:43 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ps;
	size_t	i;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	ps = ft_calloc(len + 1, sizeof(char));
	if (ps == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		ps[i] = str[i];
		i++;
	}
	ps[i] = '\0';
	return (ps);
}
