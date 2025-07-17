/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:26:45 by brivera           #+#    #+#             */
/*   Updated: 2025/03/26 23:03:59 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *news)
{
	t_list	*aux;

	if (!lst || !news)
		return ;
	if (!*lst)
	{
		*lst = news;
		return ;
	}
	aux = ft_lstlast(*lst);
	if (aux != NULL)
		aux->next = news;
	else
		return ;
}
