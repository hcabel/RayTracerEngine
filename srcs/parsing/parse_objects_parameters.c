/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects_parameters.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 09:32:14 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 22:40:02 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_object_types(t_object *obj, unsigned int *line_amount,
	char *line)
{
	(void)obj;
	(void)line_amount;
	ft_memdel((void**)&line);
	*line_amount += 1;
}

char	*parse_objects_parameters(t_object *obj, int fd,
	unsigned int *line_amount, char *line)
{
	parse_object_types(obj, line_amount, line);
	while (get_next_line(fd, &line) == 1 && line[0] == '\t')
	{
		line = ft_strtolower(line);
		if (ft_strncmp("location: {", line + 1, 11) == GOOD)
			obj->location = parse_vector(line + 11, *line_amount);
		else if (ft_strncmp("rotation: {", line + 1, 11) == GOOD)
			obj->rotation = parse_vector2d(line + 11, *line_amount);
		else if (ft_strncmp("scale: {", line + 1, 8) == GOOD)
			obj->scale = parse_vector(line + 8, *line_amount);
		else if (ft_strncmp("color: ", line + 1, 7) == GOOD)
			obj->color = parse_color(line + 8, *line_amount);
		else
			ft_printf("Parsing: %u: Object parameter does not exist\n"
				, *line_amount);
		ft_memdel((void**)&line);
		*line_amount += 1;
	}
	return (line);
}
