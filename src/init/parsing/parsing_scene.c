/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 12:03:45 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 10:55:58 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	set_component_infos(void **component, int component_type_index,
				void *target)
{
	*component = target;
	return (component_type_index);
}

static void	switch_to_parse_parameter_functions(const char *line,
				void *component, int *component_type_index,
				const unsigned int line_amount)
{
	if (*component_type_index == 1)
		parse_objects_parameters(component, line, line_amount);
	else if (*component_type_index == 2)
		parse_lights_parameters(component, line, line_amount);
	else if (*component_type_index == 3)
		parse_camera_parameters(component, line, line_amount);
	else
		ft_printf("		%u: Identification of target component failed\n",
			line_amount);
}

static int	set_new_component(t_scene *scene, t_parsing *parse,
				void **component)
{
	int	component_type_index;

	component_type_index = -1;
	if (ft_strncmp("\t[object:", parse->line, 8) == GOOD
		&& parse->shapes_index < scene->shapes_amount)
		component_type_index = set_component_infos(component, 1,
			&scene->shapes[parse->shapes_index++]);
	else if (ft_strncmp("\t[light:", parse->line, 7) == GOOD
		&& parse->light_index < scene->light_amount)
		component_type_index = set_component_infos(component, 2,
			&scene->lights[parse->light_index++]);
	else if (ft_strncmp("\t[camera:", parse->line, 7) == GOOD)
		component_type_index = set_component_infos(component, 3, &scene->cam);
	else
		ft_printf("		%u: Unknown type (can't be parsed)\n",
			parse->line_amount);
	return (component_type_index);
}

static void	parse_body(t_scene *scene, t_parsing *parse,
				void **component, int *component_type_index)
{
	if (parse->line[1] == '\t' || parse->line[1] == '[')
	{
		if (parse->line[1] == '[')
			*component_type_index = set_new_component(scene, parse, component);
		switch_to_parse_parameter_functions(parse->line + 1, *component,
			component_type_index, parse->line_amount);
	}
}

int			parse_components(t_scene *scene, int fd)
{
	t_parsing	parse;
	int			ret;
	void		*component;
	int			component_type_index;

	parse.line_amount = 1;
	parse.shapes_index = 0;
	parse.light_index = 0;
	component_type_index = 0;
	while ((ret = get_next_line(fd, &parse.line)) == 1)
	{
		parse.line = ft_strtolower(parse.line);
		if (parse.line && parse.line[0] && parse.line[0] == '\t'
			&& parse.line[1])
			parse_body(scene, &parse, &component, &component_type_index);
		ft_memdel((void**)&parse.line);
		parse.line_amount++;
	}
	return (ret != 0 ? FAILED : GOOD);
}
