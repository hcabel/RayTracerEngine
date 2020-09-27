/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:22:52 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 22:38:00 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*dispatch_component_to_parse_function(t_parsing *parse,
	char *line, t_scene *scene, int fd)
{
	if (ft_strncmp("[object:", line, 8) == GOOD
		&& parse->object_index < scene->shapes_amount)
	{
		line = parse_objects_parameters(&scene->shapes[parse->object_index], fd,
			&parse->line_amount, line);
		parse->object_index++;
	}
	else if (ft_strncmp("[light:", line, 7) == GOOD
		&& parse->light_index < scene->light_amount)
	{
		line = parse_lights_parameters(&scene->lights[parse->light_index], fd,
			&parse->line_amount, line);
		parse->light_index++;
	}
	else
	{
		ft_memdel((void**)&line);
		if (parse->light_index > scene->light_amount
			|| parse->object_index > scene->shapes_amount)
			ft_printf("{r}Parsing: %u: Not enough component allocated{y}\n",
				parse->line_amount);
	}
	return (line);
}

int			parse_components(t_scene *scene, int fd)
{
	t_parsing	parse;
	char		*line;
	int			ret;

	parse.line_amount = 0;
	parse.object_index = 0;
	parse.light_index = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		parse.line_amount++;
		while (line && line[0] && line[0] == '[')
		{
			line = dispatch_component_to_parse_function(&parse, line,
				scene, fd);
		}
		ft_memdel((void**)&line);
	}
	return (ret == -1 ? FAILED : GOOD);
}
