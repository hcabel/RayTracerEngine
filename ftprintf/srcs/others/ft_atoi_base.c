/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 18:11:42 by exam              #+#    #+#             */
/*   Updated: 2019/09/14 14:51:31 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	find_value(char c, unsigned int base)
{
	if (c >= '0' && c <= '9')
		return ((unsigned int)(c - 48) < base ? c - 48 : -1);
	if (c >= 'A' && c <= 'Z')
		return ((unsigned int)(c - 65 + 10) < base ? c - 65 + 10 : -1);
	return ((unsigned int)(c - 97 + 10) < base ? c - 97 + 10 : -1);
}

int			ft_atoi_base(const char *nbr, unsigned int base)
{
	int	result;
	int	i;
	int	value;
	int	signe;

	i = 0;
	result = 0;
	signe = 1;
	if (nbr[i] == '-')
	{
		signe = -1;
		i++;
	}
	while (nbr[i])
	{
		if ((value = find_value(nbr[i], base)) == -1)
			return (0);
		result *= base;
		result += value;
		i++;
	}
	return (result * signe);
}
