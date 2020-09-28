/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights_parameters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 18:21:04 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/28 14:13:32 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_light_type(t_light *light, char *line,
				unsigned int line_amount)
{
	(void)light;
	(void)line;
	(void)line_amount;
}

void		parse_lights_parameters(t_light *light, char *line,
				unsigned int line_amount)
{
	if (line[0] == '[')
		parse_light_type(light, line, line_amount);
	else if (ft_strncmp("location: {", line + 1, 11) == GOOD)
		light->location = parse_vector(line + 11, line_amount);
	else if (ft_strncmp("rotation: {", line + 1, 11) == GOOD)
		light->rotation = parse_vector2d(line + 11, line_amount);
	else if (ft_strncmp("intensity: ", line + 1, 11) == GOOD)
		light->intensity = ft_atoi(line + 12);
	else
		ft_printf("Parsing: %u: Light parameter does not exist\n", line_amount);
}
