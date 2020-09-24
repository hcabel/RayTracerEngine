/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:14:54 by hcabel            #+#    #+#             */
/*   Updated: 2019/04/09 14:44:49 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int result;
	int cond;

	cond = 1;
	result = 0;
	while (*str == '\n' || *str == '\t' || *str == '\v' ||
			*str == ' ' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		cond = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!(*str && *str >= '0' && *str <= '9'))
		return (0);
	while (*str && *str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * cond);
}
