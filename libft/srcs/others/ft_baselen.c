/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baselen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:49:20 by hcabel            #+#    #+#             */
/*   Updated: 2019/09/14 14:40:48 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_baselen(long long nbr, int base)
{
	unsigned long long	cast;
	int					result;

	cast = (nbr < 0 && base == 10 ? -nbr : nbr);
	result = (nbr < 0 && base == 10 ? 2 : 1);
	while ((cast /= base) > 0)
		result++;
	return (result);
}
