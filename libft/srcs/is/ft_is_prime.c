/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:27:05 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/11 16:12:48 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_is_prime(size_t nb)
{
	size_t i;

	i = 0;
	while (i <= (nb / 2))
	{
		if (i != nb && i != 1 && i != 0 && !(nb % i))
			return (0);
		i++;
	}
	return (1);
}
