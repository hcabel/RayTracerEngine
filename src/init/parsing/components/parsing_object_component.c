/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_object_component.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:25:08 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:28:18 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_object_type(t_object *object, const char *line)
{
	if (ft_strncmp("sphere]", line, 7) == GOOD)
		object->sdf_index = 0;
	else if (ft_strncmp("cone]", line, 5) == GOOD)
		object->sdf_index = 1;
	else if (ft_strncmp("cube]", line, 5) == GOOD)
		object->sdf_index = 2;
	else if (ft_strncmp("cylinder]", line, 9) == GOOD)
		object->sdf_index = 3;
	else if (ft_strncmp("plane]", line, 6) == GOOD)
		object->sdf_index = 4;
}

void		parse_objects_parameters(t_object *object, const char *line,
				const unsigned int line_amount)
{
	if (line[0] == '[')
		parse_object_type(object, line + 8);
	else if (ft_strncmp("location: {", line + 1, 11) == GOOD)
		object->location = parse_vector(line + 11, line_amount);
	else if (ft_strncmp("scale: {", line + 1, 8) == GOOD)
		object->scale = parse_vector(line + 8, line_amount);
	else if (ft_strncmp("rotation: {", line + 1, 11) == GOOD)
		object->rotation = parse_vector2d(line + 11, line_amount);
	else if (ft_strncmp("color: ", line + 1, 7) == GOOD)
		object->color = parse_color(line + 8, line_amount);
	else
		ft_printf("		%u: Object parameter does not exist\n",
			line_amount);
}
