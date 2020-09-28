/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_components.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 18:22:52 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/28 14:10:58 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	set_component_infos(void **component, int component_type_index,
				void *target)
{
	*component = target;
	return (component_type_index);
}

static void	switch_to_parse_parameter_functions(char *line, int line_amount,
				void *component, int *component_type_index)
{
	if (*component_type_index == 1)
		parse_objects_parameters(component, line, line_amount);
	else if (*component_type_index == 2)
		parse_lights_parameters(component, line, line_amount);
	else
		ft_printf("	%u: Identification of target component failed\n",
			line_amount);
}

static void	set_new_component(t_scene *scene, t_parsing *parse, char *line,
				void **component, int *component_type_index)
{
	*component_type_index = 0;
	if (ft_strncmp("[object:", line, 8) == GOOD
		&& parse->shapes_index < scene->shapes_amount)
		*component_type_index = set_component_infos(component, 1,
			&scene->shapes[parse->shapes_index++]);
	else if (ft_strncmp("[light:", line, 7) == GOOD
		&& parse->light_index < scene->light_amount)
		*component_type_index = set_component_infos(component, 2,
			&scene->lights[parse->light_index++]);
	else
		ft_printf("	%u: Unknown type (can't be parsed)\n", parse->line_amount);
}

int			parse_components(t_scene *scene, int fd)
{
	t_parsing	parse;
	char		*line;
	int			ret;
	void		*component;
	int			component_type_index;

	parse.line_amount = 0;
	parse.shapes_index = 0;
	parse.light_index = 0;
	component_type_index = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		line = ft_strtolower(line);
		parse.line_amount++;
		if (line && line[0] && line[0] == '[')
			set_new_component(scene, &parse, line,
				&component, &component_type_index);
		else if (line && line[0] && line[0] == '\t')
			switch_to_parse_parameter_functions(line, parse.line_amount,
				component, &component_type_index);
		ft_memdel((void**)&line);
	}
	return (ret == -1 ? FAILED : GOOD);
}
