/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:50:48 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/10 13:02:31 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

char	*ft_strnstr(const char *haystack, char *needle, size_t len)
{
	size_t i;
	size_t i2;

	i = 0;
	if (*haystack == '\0' && *needle != '\0')
		return (NULL);
	if (*haystack == '\0' || *needle == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		if (i >= len)
			return (0);
		i2 = 0;
		while (haystack[i + i2] == needle[i2])
		{
			if (i + i2 >= len)
				return (0);
			i2++;
			if (needle[i2] == '\0')
				return ((char*)haystack + i);
		}
		i++;
	}
	return (0);
}
