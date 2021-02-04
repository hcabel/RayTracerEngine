/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:30:09 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 15:17:28 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static char		*rounding_realloc(char *str, int sign)
{
	char	*new_str;
	int		i;

	i = ft_strlen(str);
	if (!(new_str = (char*)ft_memalloc(sizeof(char) * (i + 1 + sign))))
		return (NULL);
	i = sign;
	while (str[i - sign])
	{
		new_str[i] = str[i - sign];
		i++;
	}
	if (sign)
	{
		new_str[0] = '-';
		new_str[1] = '1';
	}
	else
		new_str[0] = '1';
	return (new_str);
}

static void		decimal_rounding(char **str_addr, int i)
{
	char	*str;

	str = *str_addr;
	while (str[i] == '9' && i > 0)
	{
		str[i] = '0';
		i--;
		if (str[i] == '.')
			i--;
	}
	if (str[i] == '-')
		*str_addr = rounding_realloc(*str_addr, 1);
	else if (i == -1)
		*str_addr = rounding_realloc(*str_addr, 0);
	else if (str[i] != '9')
		str[i] += 1;
}

static void		decimal(char **str_addr, double deci, int precis, int len)
{
	int		i;
	char	*str;

	str = *str_addr;
	i = len;
	if (precis > 1)
		str[i++] = '.';
	while (precis > 1)
	{
		precis--;
		deci *= 10;
		str[i] = (long int)deci % 10 + '0';
		i++;
		deci -= (int)deci % 10;
	}
	i--;
	deci *= 10;
	if ((long int)deci % 10 >= 5)
	{
		if (str[i] != '9')
			str[i] += 1;
		else
			decimal_rounding(str_addr, i);
	}
}

static void		ft_itoa_float(char **str_addr, int n, int len)
{
	int		sign;
	char	*str;

	str = *str_addr;
	sign = 1;
	if (n == 0)
		str[len] = '0';
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	while (n > 0)
	{
		str[len--] = n % 10 + 48;
		n = n / 10;
	}
	if (sign == -1)
		str[len--] = '-';
}

char			*ft_ftoa(long double n, int precis)
{
	long int	whole;
	int			len;
	char		*str;

	precis++;
	whole = (long int)n;
	len = ft_nbrlen(whole);
	if (!(str = (char*)ft_memalloc(sizeof(*str) * (len + precis + 2))))
		return (NULL);
	str[len + precis + 1] = '\0';
	ft_itoa_float(&str, whole, len - 1);
	decimal(&str, FABS(n - (long double)whole), precis, len);
	return (str);
}
