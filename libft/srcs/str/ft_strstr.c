/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 18:39:16 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/10 16:25:22 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int i2;

	i = 0;
	if (*haystack == '\0' && *needle != '\0')
		return (0);
	if (*haystack == '\0' || *needle == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		i2 = 0;
		while (haystack[i + i2] == needle[i2])
		{
			i2++;
			if (needle[i2] == '\0')
				return ((char*)haystack + i);
		}
		i++;
	}
	return (0);
}
