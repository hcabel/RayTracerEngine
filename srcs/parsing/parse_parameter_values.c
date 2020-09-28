/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameter_values.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 11:55:06 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/28 14:17:47 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	parse_vector(char *line, unsigned int line_amount)
{
	t_vector	res;
	int			index;

	res = newvector(0, 0, 0);
	if (line[0] != '{')
		return (res);
	res.x = ft_atoi(line + 1);
	index = ft_nbrlen(res.x) + (res.x == 0 && line[1] == '-' ? 2 : 1);
	if (line[index] != '}')
	{
		while(line[index] && !ft_isdigit(line[index]) && line[index] != '-')
			index++;
		res.y = ft_atoi(line + index);
		index += ft_nbrlen(res.y) + (res.y == 0 && line[index] == '-' ? 1 : 0);
		while(line[index] && !ft_isdigit(line[index]) && line[index] != '-')
			index++;
		res.z = ft_atoi(line + index);
		index += ft_nbrlen(res.z) + (res.z == 0 && line[index] == '-' ? 1 : 0);
		if (!line[index] || line[index] != '}')
			ft_printf("	%u: Value parsing failed\n", line_amount);
		return (!line[index] || line[index] != '}' ? newvector(0, 0, 0) : res);
	}
	res.y = res.x;
	res.z = res.x;
	return (res);
}

t_vector2d	parse_vector2d(char *line, unsigned int line_amount)
{
	t_vector2d	result;
	int			index;

	result = newvector2d(0, 0);
	if (line[0] != '{')
		return (result);
	result.x = ft_atoi(line + 1);
	index = ft_nbrlen(result.x) + 2;
	if (line[index] != '}')
	{
		while(line[index] && !ft_isdigit(line[index]) && line[index] != '-')
			index++;
		result.y = ft_atoi(line + index);
		index += ft_nbrlen(result.y);
		if (!line[index] || line[index] != '}')
		{
			ft_printf("Parsing: %u: Value parsing failed\n", line_amount);
			result = newvector2d(0, 0);
		}
	}
	else
		result.y = result.x;
	return (result);
}

t_vector	parse_color(char *line, unsigned int line_amount)
{
	t_vector	result;
	int			hexcolor;

	result = newvector(0, 0, 0);
	hexcolor = -1;
	if (line[0] == '{')
	{
		result = parse_vector(line, line_amount);
		result.x = fmaxf(result.x, 255);
		result.y = fmaxf(result.y, 255);
		result.z = fmaxf(result.z, 255);
	}
	else if (line[0] == '0' && line[1] == 'x')
	{
		hexcolor = ft_atoi_base(line + 2, 16);
		result.x = (hexcolor >> 16) & 0xFF;
		result.y = (hexcolor >> 8) & 0xFF;
		result.z = hexcolor & 0xFF;
	}
	else
		ft_printf("Parsing: %u: Color parsing failed\n",
			line_amount);
	return (result);
}
