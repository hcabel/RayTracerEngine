/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:23:03 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/05 13:35:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	pf_putstr(char *str, int i, int *ret)
{
	int	j;

	j = 0;
	while (1)
	{
		if (!str[i + j] || str[i + j] == '%'
			|| (str[i + j] == '{' && str[i + j - 1] != '%'))
			break ;
		else
			j++;
	}
	write(1, str + i, j);
	*ret += j;
	return (j);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		ret;
	char	*str;

	str = (char*)format;
	va_start(args, format);
	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '%' || str[i] == '{')
			i += pf_dispatch(args, str + i, &ret);
		else
			i += pf_putstr(str, i, &ret);
	}
	va_end(args);
	return (ret);
}
