/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-07-18 09:40:12 by brivera           #+#    #+#             */
/*   Updated: 2025-07-18 09:40:12 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees a NULL-terminated array of strings and the array itself.
 * 
 * @param array The array to free (may be NULL)
 * @return Always returns NULL to allow convenient assignment in calling code
 *         Example usage: array = free_array(array);
 * 
 * @note This function safely handles NULL input and properly frees all
 *       allocated strings in the array before freeing the array pointer.
 *       After calling, the array pointer should be set to NULL to avoid
 *       dangling references.
 */

void	ft_free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	*ft_free_array(char **array)
{
	size_t	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		ft_free_ptr((void **)&array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}
