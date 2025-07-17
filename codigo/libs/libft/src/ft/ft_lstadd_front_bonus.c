/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:26:58 by brivera           #+#    #+#             */
/*   Updated: 2025/02/27 19:23:43 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *news)
{
	if (!lst || !news)
		return ;
	news->next = *lst;
	*lst = news;
}
