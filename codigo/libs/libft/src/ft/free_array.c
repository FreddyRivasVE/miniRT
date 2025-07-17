/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:59:13 by brivera           #+#    #+#             */
/*   Updated: 2025/05/11 12:48:00 by brivera          ###   ########.fr       */
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

static void	ft_free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	*free_array(char **array)
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
