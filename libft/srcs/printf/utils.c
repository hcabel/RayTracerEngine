/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:06:05 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/05 13:35:20 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int				add_to_str(char *add, char **str_addr, int current, int end)
{
	int		i;
	char	*str;

	str = *str_addr;
	i = 0;
	while (i < end && add[i])
	{
		str[i + current] = add[i];
		i++;
	}
	return (i);
}

int				fill(int size, char c, char **str_addr, int current)
{
	char	*str;
	int		i;

	str = *str_addr;
	i = 0;
	while (i < size)
	{
		str[i + current] = c;
		i++;
	}
	return (i);
}

int				ft_ubaselen(unsigned long long nbr, int base)
{
	int	result;

	result = 1;
	while ((nbr /= base) > 0)
		result++;
	return (result);
}

static char		get_value(int value, char c)
{
	if (value < 10)
		return (value + '0');
	return (value + c - 10);
}

char			*ft_utoa_base(unsigned long long nbr, int base, char c)
{
	char	*result;
	int		size;
	int		i;

	size = ft_ubaselen(nbr, base);
	if (!(result = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	result[size] = '\0';
	i = size - 1;
	if (nbr == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	while (nbr > 0)
	{
		result[i] = get_value(nbr % base, c);
		nbr /= base;
		i--;
	}
	return (result);
}
