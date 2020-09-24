/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:47:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/14 14:52:31 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	get_value(int value)
{
	if (value < 10)
		return (value + '0');
	return (value + 'a' - 10);
}

char		*ft_itoa_base(long long nbr, int base)
{
	unsigned long long	cast;
	char				*result;
	int					size;
	int					i;

	cast = (base <= 10 && nbr < 0 ? -nbr : nbr);
	size = ft_baselen(nbr, base);
	if (!(result = (char*)malloc(sizeof(char) * size)))
		return (NULL);
	result[size] = '\0';
	result[0] = (nbr < 0 && base <= 10 ? '-' : '\0');
	i = size - 1;
	if (cast == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	while (cast > 0)
	{
		result[i] = get_value(cast % base);
		cast /= base;
		i--;
	}
	return (result);
}
