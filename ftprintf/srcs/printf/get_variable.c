/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:45:37 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/23 22:13:57 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static char	*cast_to_str2(t_flags flags, void *arg)
{
	if (flags.type == 'u')
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 10, 'a'));
		else
			return (ft_utoa_base((unsigned int)(long)arg, 10, 'a'));
	else if (flags.type == 'f')
	{
		if (flags.scale[0] == 'L')
			return (ft_ftoa(*(long double*)arg,
				(flags.precis == -1 ? 6 : flags.precis)));
		else
			return (ft_ftoa(*(double*)arg,
				(flags.precis == -1 ? 6 : flags.precis)));
	}
	return (NULL);
}

static char	*cast_to_str(t_flags flags, void *arg)
{
	if (flags.type == 'd' || flags.type == 'i')
		if (flags.scale[0] == 'l')
			return (ft_itoa_base((long long)((long)arg), 10));
		else
			return (ft_itoa_base((long long)((int)(long)arg), 10));
	else if (flags.type == 'o')
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 8, 'a'));
		else
			return (ft_utoa_base((unsigned int)(long)arg, 8, 'a'));
	else if (flags.type == 'x')
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 16, 'a'));
		else
			return (ft_utoa_base((unsigned int)(long)arg, 16, 'a'));
	else if (flags.type == 'X')
		if (flags.scale[0] == 'l')
			return (ft_utoa_base((unsigned long)arg, 16, 'A'));
		else
			return (ft_utoa_base((unsigned int)(long)arg, 16, 'A'));
	else
		return (cast_to_str2(flags, arg));
}

char		*convert_to_char(void *arg, t_flags flags, t_newvalues *nv)
{
	char	*str;

	str = NULL;
	if (flags.type == 'c' || flags.type == '%')
	{
		if (!(str = (char*)malloc(sizeof(char) * 1)))
			return (NULL);
		str[0] = (flags.type == 'c' ? (char)(long)arg : '%');
		str[1] = '\0';
	}
	else if (flags.type == 's')
	{
		if ((char*)arg != NULL)
			str = (char*)(arg);
		else
			str = "(null)";
	}
	else if (flags.type == 'p')
		str = ft_utoa_base((unsigned long)arg, 16, 'a');
	else
		str = cast_to_str(flags, arg);
	if (flags.type == 'd' && str[0] == '-')
		nv->is_negative = 1;
	return (str);
}
