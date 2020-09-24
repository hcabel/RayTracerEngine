/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:23:19 by hcabel            #+#    #+#             */
/*   Updated: 2019/10/08 15:41:21 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define ZERO_SIZE (nv->zero_size > 0 ? nv->zero_size : 0)
# define SPACE_SIZE (nv->space_size > 0 ? nv->space_size : 0)
# define IS_MINUS flags.options[0]
# define IS_PLUS flags.options[1]
# define IS_HASHTAG flags.options[2]
# define IS_0 flags.options[3]
# define IS_SPACE flags.options[4]
# define IS_NEGA nv->is_negative

# define ADDTOSTR(x) add_to_str(x, &nv->new_str, i, nv->str_size)

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

typedef struct	s_flags
{
	char		options[5];
	int			length;
	int			precis;
	char		scale[2];
	char		type;
}				t_flags;

typedef struct	s_newvalues
{
	int			arg_size;
	int			space_size;
	int			zero_size;
	int			is_negative;
	int			str_size;
	char		*new_str;

}				t_newvalues;

/*
**	ft_printf.c
*/
int				ft_printf(const char *format, ...);

/*
**	pf_dispatch.c
*/
int				pf_dispatch(va_list args, char *str, int *ret);
int				add_hashtag(char *str_arg, t_flags flags
					, t_newvalues *nv, int i);

/*
**	pf_parse_flags.c
*/
int				pf_parse_flags(t_flags *flags, char *str);

/*
**	pf_modify_value.c
*/
int				pf_modify_value(void *arg, t_flags flags);

/*
**	get_variable.c
*/
char			*convert_to_char(void *arg, t_flags flags, t_newvalues *nv);

/*
**	utils.c
*/
int				add_to_str(char *add, char **str_addr, int current, int end);
int				fill(int size, char c, char **str_addr, int current);
int				ft_ubaselen(unsigned long long nbr, int base);
char			*ft_utoa_base(unsigned long long nbr, int base, char c);

/*
**	ft_ftoa.c
*/
char			*ft_ftoa(long double n, int precis);

/*
**	colour.c
*/
int				colour_parse(char *str);

#endif
