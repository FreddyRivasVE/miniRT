/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:38:58 by brivera           #+#    #+#             */
/*   Updated: 2024/10/11 15:39:20 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_countnum(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
	{
		count++;
	}
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	ft_putstrnum(char n, char *strnum, size_t i)
{
	strnum[i] = n;
}

static char	*ft_putn(int n, char *strnum, size_t num)
{
	if (n <= 9 && n >= 0)
	{
		ft_putstrnum((n % 10 + '0'), strnum, num);
		return (strnum);
	}
	else
	{
		ft_putn((n / 10), strnum, num - 1);
		ft_putstrnum((n % 10 + '0'), strnum, num);
	}
	strnum[num + 1] = '\0';
	return (strnum);
}

char	*ft_itoa(int n)
{
	char		*strnum;
	size_t		num;

	if (n == INT_MIN)
	{
		strnum = ft_strdup("-2147483648");
		if (strnum == NULL)
			return (NULL);
		return (strnum);
	}
	num = ft_countnum(n);
	strnum = (char *)malloc(num + 1);
	if (strnum == NULL)
		return (NULL);
	if (n < 0)
	{
		ft_putstrnum('-', strnum, 0);
		n = -n;
	}
	ft_putn(n, strnum, num - 1);
	strnum[num] = '\0';
	return (strnum);
}
