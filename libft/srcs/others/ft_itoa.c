/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 15:00:46 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/15 14:16:39 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		count_memory(long long nb)
{
	int		i;
	int		n;

	n = nb;
	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		if (n == -2147483648)
			return (11);
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

static void		setnu(char *tab, long long nb, int size)
{
	int i;

	i = 1;
	while (nb > 0 && size - i >= 0)
	{
		tab[size - i] = nb % 10 + '0';
		i++;
		nb /= 10;
	}
}

char			*ft_itoa(long long n)
{
	char	*tab;
	int		size;

	size = count_memory(n);
	if (!(tab = (char*)malloc(sizeof(*tab) * (size + 1))))
		return (NULL);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			n = -147483648;
			tab[1] = '2';
		}
		setnu(tab, n *= -1, size);
		tab[0] = '-';
	}
	else if (n == 0)
		tab[0] = '0';
	else
		setnu(tab, n, size);
	tab[size] = '\0';
	return (tab);
}
