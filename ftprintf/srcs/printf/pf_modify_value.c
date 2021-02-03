/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_modify_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:33:03 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 14:07:54 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

static void	add_flags(t_flags flags, t_newvalues *nv)
{
	if ((IS_PLUS && !IS_NEGA) || (flags.type == 'o' && IS_HASHTAG))
		nv->space_size--;
	else if (IS_NEGA)
		nv->space_size--;
	if (IS_SPACE && !IS_PLUS && !IS_NEGA)
		nv->space_size--;
	if (IS_0)
	{
		if (flags.precis != -1)
			while ((nv->zero_size += 1) + nv->arg_size < flags.precis)
				nv->space_size -= 1;
		else
			nv->zero_size += nv->space_size + 1;
		nv->space_size = (flags.precis != -1 ? nv->space_size : 0);
		nv->zero_size -= 1;
	}
	if ((flags.type == 'x' || flags.type == 'X') && IS_HASHTAG)
		nv->space_size -= 2;
}

static void	set_additional_size(t_flags flags, t_newvalues *nv)
{
	if (!(flags.precis == -1 && flags.length != -1))
	{
		if (flags.precis > nv->arg_size && flags.type != 's')
			nv->zero_size = flags.precis - nv->arg_size;
		else if (flags.precis != -1 && flags.precis < nv->arg_size
			&& flags.type == 's')
			nv->arg_size = flags.precis;
		if (flags.type == 'o' && IS_HASHTAG)
			nv->zero_size -= 1;
		if (flags.length != -1)
			if (flags.length > nv->zero_size + nv->arg_size)
				nv->space_size = flags.length - (nv->zero_size + nv->arg_size);
	}
	else if (flags.length > nv->arg_size)
		nv->space_size = flags.length - nv->arg_size;
	add_flags(flags, nv);
}

static void	create_new_str(t_flags flags, t_newvalues *nv, char *str_arg)
{
	nv->str_size = ZERO_SIZE + SPACE_SIZE + nv->arg_size;
	if (IS_HASHTAG)
	{
		if (flags.type == 'o' && str_arg[0] != '0')
			nv->str_size += 1;
		else if (flags.type == 'f')
			nv->str_size += 1;
		else if ((flags.type == 'x' || flags.type == 'X')
			&& str_arg[0] != '0')
			nv->str_size += 2;
	}
	if (IS_NEGA || IS_PLUS)
		nv->str_size++;
	else if (IS_SPACE)
		nv->str_size++;
	if (!(nv->new_str = (char*)malloc(sizeof(char) * (nv->str_size))))
		return ;
	ft_bzero(nv->new_str, nv->str_size);
}

static void	create_new_arg(char *str_arg, t_flags flags, t_newvalues *nv)
{
	int	i;

	set_additional_size(flags, nv);
	create_new_str(flags, nv, str_arg);
	i = 0;
	if (!IS_MINUS)
		i += fill(nv->space_size, ' ', &nv->new_str, i);
	if (IS_HASHTAG || flags.type == 'p')
		i = add_hashtag(str_arg, flags, nv, i);
	else if (IS_PLUS && !IS_NEGA)
		i += ADDTOSTR("+");
	else if (IS_SPACE && !IS_PLUS && !IS_NEGA)
		i += ADDTOSTR(" ");
	else if (IS_NEGA && flags.type != 'u')
		i += ADDTOSTR("-");
	if (flags.type != 's' && flags.type != 'c')
		i += fill(nv->zero_size, '0', &(nv->new_str), i);
	i += add_to_str(str_arg + IS_NEGA, &(nv->new_str), i, nv->arg_size);
	if (flags.type == 'f' && IS_HASHTAG && !ft_strchr(str_arg, '.'))
		i += ADDTOSTR(".");
	if (IS_MINUS)
		i += fill(nv->space_size, ' ', &(nv->new_str), i);
}

int			pf_modify_value(void *arg, t_flags flags)
{
	t_newvalues	nv;
	char		*old_arg_str;

	nv.space_size = 0;
	nv.zero_size = 0;
	nv.is_negative = 0;
	if ((old_arg_str = convert_to_char(arg, flags, &nv)) == NULL)
		return (0);
	nv.arg_size = ft_strlen(old_arg_str) - nv.is_negative;
	if (flags.type == 'p')
		nv.arg_size += 2;
	else if (flags.type == 'c' && old_arg_str[0] == '\0')
		nv.arg_size = 1;
	if (flags.precis == 0 && (int)(long)arg == 0
		&& (flags.type != 'o' || !IS_HASHTAG))
		nv.arg_size = 0;
	create_new_arg(old_arg_str, flags, &nv);
	write(1, nv.new_str, nv.str_size);
	if (flags.type != 's')
		ft_memdel((void**)&old_arg_str);
	ft_memdel((void**)&nv.new_str);
	return (nv.str_size);
}
