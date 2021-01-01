/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_structures.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:29:24 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/24 12:30:09 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	parse_color(char *line, unsigned int line_amount)
{
	t_vector	result;
	int			hexcolor;

	result = new_vector(0, 0, 0);
	hexcolor = -1;
	if (line[0] == '{')
	{
		result = parse_vector(line, line_amount);
		result.x = fmaxf(fminf(result.x, 255), 0);
		result.y = fmaxf(fminf(result.y, 255), 0);
		result.z = fmaxf(fminf(result.z, 255), 0);
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