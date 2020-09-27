/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 09:56:23 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 10:26:21 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) && str[i] > 64 && str[i] < 91)
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}
