/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_parameters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 09:32:14 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/28 14:13:26 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_object_type(t_object *object, char *line,
				unsigned int line_amount)
{
	(void)object;
	(void)line;
	(void)line_amount;
}

void	parse_objects_parameters(t_object *object, char *line,
			unsigned int line_amount)
{
	if (line[0] == '[')
		parse_object_type(object, line, line_amount);
	else if (ft_strncmp("location: {", line + 1, 11) == GOOD)
		object->location = parse_vector(line + 11, line_amount);
	else if (ft_strncmp("rotation: {", line + 1, 11) == GOOD)
		object->rotation = parse_vector2d(line + 11, line_amount);
	else if (ft_strncmp("scale: {", line + 1, 8) == GOOD)
		object->scale = parse_vector(line + 8, line_amount);
	else if (ft_strncmp("color: ", line + 1, 7) == GOOD)
		object->scale = parse_vector(line + 7, line_amount);
	else
		ft_printf("Parsing: %u: Object parameter does not exist\n", line_amount);
}
