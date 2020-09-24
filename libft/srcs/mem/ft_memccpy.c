/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:12:12 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/10 19:04:09 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dstc;
	unsigned char	*srcc;
	unsigned char	cc;
	size_t			i;

	srcc = (unsigned char*)src;
	dstc = (unsigned char*)dst;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		dstc[i] = srcc[i];
		if (srcc[i] == cc)
			return (unsigned char*)(dst + i + 1);
		i++;
	}
	return (0);
}
