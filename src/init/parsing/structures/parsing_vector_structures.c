/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_vector_structures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:29:00 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 19:10:11 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	parse_vector(const char *line, const unsigned int line_amount)
{
	t_vector	res;
	int			index;

	res = new_vector(0, 0, 0);
	if (line[0] != '{')
		return (res);
	res.x = ft_atoi(line + 1);
	index = ft_nbrlen(res.x) + (res.x == 0 && line[1] == '-' ? 2 : 1);
	if (line[index] != '}')
	{
		while (line[index] && !ft_isdigit(line[index]) && line[index] != '-')
			index++;
		res.y = ft_atoi(line + index);
		index += ft_nbrlen(res.y) + (res.y == 0 && line[index] == '-' ? 1 : 0);
		while (line[index] && !ft_isdigit(line[index]) && line[index] != '-')
			index++;
		res.z = ft_atoi(line + index);
		index += ft_nbrlen(res.z) + (res.z == 0 && line[index] == '-' ? 1 : 0);
		if (!line[index] || line[index] != '}')
			ft_printf("		%u: Value parsing failed\n", line_amount);
		return (!line[index] || line[index] != '}' ? new_vector(0, 0, 0) : res);
	}
	res.y = res.x;
	res.z = res.x;
	return (res);
}

t_vector2d	parse_vector2d(const char *line, const unsigned int line_amount)
{
	t_vector2d	result;
	int			index;

	result = new_vector2d(0, 0);
	if (line[0] != '{')
		return (result);
	result.x = ft_atoi(line + 1);
	index = ft_nbrlen(result.x) + 2;
	if (line[index] != '}')
	{
		while (line[index] && !ft_isdigit(line[index]) && line[index] != '-')
			index++;
		result.y = ft_atoi(line + index);
		index += ft_nbrlen(result.y);
		if (!line[index] || line[index] != '}')
		{
			ft_printf("		%u: Value parsing failed\n", line_amount);
			result = new_vector2d(0, 0);
		}
	}
	else
		result.y = result.x;
	return (result);
}
