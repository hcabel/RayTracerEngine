/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:23:47 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/08 13:39:30 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_nbrlen(long long nbr)
{
	int					result;
	unsigned long long	cast;

	result = (nbr < 0 ? 2 : 1);
	cast = (nbr < 0 ? -nbr : nbr);
	while ((cast /= 10) > 0)
		result++;
	return (result);
}
