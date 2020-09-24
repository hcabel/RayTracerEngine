/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 23:34:35 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/14 14:52:00 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long		find_value(char value, char *to_base, long base_length)
{
	long i;

	i = 0;
	while (to_base[i] != value && i <= base_length)
		i++;
	return (i <= base_length ? i : -1);
}

static long		conv_to_long(char *nbr, char *base, long base_length)
{
	long	i;
	int		negative;
	long	result;

	i = 0;
	while (nbr[i] && (nbr[i] <= ' ' || nbr[i] > '~'))
		i++;
	negative = (nbr[i] == '-' ? -1 : 1);
	i += (nbr[i] == '-' || nbr[i] == '+' ? 1 : 0);
	result = 0;
	while (nbr[i] && find_value(nbr[i], base, base_length) != (long)-1)
	{
		result = result * base_length + find_value(nbr[i], base, base_length);
		i++;
	}
	return (result * negative);
}

static long		get_size(long nbr, long base_length)
{
	long	length;
	long	number;

	length = (nbr < 0 ? 1 : 0);
	number = (nbr < 0 ? nbr * -1 : nbr);
	while (number >= base_length)
	{
		length++;
		number /= base_length;
	}
	return (++length);
}

static void		setup(char **result_adr, char *base_to, long value, long size)
{
	long	i;
	long	base_length;
	char	*result;
	int		stop;

	result = *result_adr;
	base_length = 0;
	while (base_to[base_length])
		base_length++;
	result[0] = (value < 0 ? '-' : '+');
	stop = (value < 0 ? 1 : 0);
	value *= (value < 0 ? -1 : 1);
	i = size - 1;
	while (value >= 0 && i >= stop)
	{
		result[i] = base_to[value % base_length];
		i--;
		value /= base_length;
	}
	result[size] = '\0';
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	char			*result;
	long			value;
	long			size;
	long			base_length;

	if (!nbr || !base_from || !base_to)
		return (0);
	base_length = 0;
	while (base_from[base_length])
		base_length++;
	value = conv_to_long(nbr, base_from, base_length);
	base_length = 0;
	while (base_to[base_length])
		base_length++;
	size = get_size(value, base_length);
	result = malloc(sizeof(char) * size);
	setup(&result, base_to, value, size);
	return (result);
}
