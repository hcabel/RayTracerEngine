/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera_parameters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:52:24 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/01 17:55:00 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_camera_type(t_cam *cam, char *line,
				unsigned int line_amount)
{
	(void)cam;
	(void)line;
	(void)line_amount;
}

void	parse_camera_parameters(t_cam *cam, char *line,
			unsigned int line_amount)
{
	if (line[0] == '[')
		parse_camera_type(cam, line, line_amount);
	else if (ft_strncmp("location: {", line + 1, 11) == GOOD)
		cam->location = parse_vector(line + 11, line_amount);
	else if (ft_strncmp("rotation: {", line + 1, 11) == GOOD)
		cam->rotation = parse_vector2d(line + 11, line_amount);
	else
		ft_printf("Parsing: %u: Object parameter does not exist\n", line_amount);
}
