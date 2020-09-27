/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights_parameters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:21:04 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 22:40:06 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_lights_types(t_light *light, unsigned int *line_amount,
	char *line)
{
	(void)light;
	(void)line_amount;
	ft_memdel((void**)&line);
	*line_amount += 1;
}

char	*parse_lights_parameters(t_light *light, int fd,
	unsigned int *line_amount, char *line)
{
	parse_lights_types(light, line_amount, line);
	while (get_next_line(fd, &line) == 1 && line[0] == '\t')
	{
		line = ft_strtolower(line);
		if (ft_strncmp("location: {", line + 1, 11) == GOOD)
			light->location = parse_vector(line + 11, *line_amount);
		else if (ft_strncmp("rotation: {", line + 1, 11) == GOOD)
			light->rotation = parse_vector2d(line + 11, *line_amount);
		else if (ft_strncmp("intensity: ", line + 1, 11) == GOOD)
			light->intensity = ft_atoi(line + 12);
		else
			ft_printf("Parsing: %u: Light parameter does not exist\n"
				, *line_amount);
		ft_memdel((void**)&line);
		*line_amount += 1;
	}
	return (line);
}
