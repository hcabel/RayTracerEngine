/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_primary_infos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:22:48 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 22:09:08 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	verif_light_type(char *line)
{
	if (ft_strncmp("point]", line, 7) == GOOD)
		return (GOOD);
	return (FAILED);
}

static int	verif_object_type(char *line)
{
	if (ft_strncmp("sphere]", line, 8) == GOOD)
		return (GOOD);
	return (FAILED);
}

static void	check_component_format(t_scene *scene, char *line, int line_amount)
{
	if (ft_strncmp("[object:", line, 8) == GOOD)
	{
		if (verif_object_type(line + 8) == GOOD)
			scene->shapes_amount++;
		else
			ft_printf("Parsing: %d: object type doesn't exit\n",
				line_amount);
	}
	else if (ft_strncmp("[light:", line, 7) == GOOD)
	{
		if (verif_light_type(line + 7) == GOOD)
			scene->light_amount++;
		else
			ft_printf("Parsing: %u: Light type doesn't exit\n",
				line_amount);
	}
	else
		ft_printf("Parsing: %u: Type unkown\n", line_amount);
}

int			parse_component_amount(t_scene *scene, int fd)
{
	char			*line;
	int				ret;
	unsigned int	line_amount;

	line_amount = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (line[0] && line[0] == '[')
			check_component_format(scene, line, line_amount);
		else if (line[0] != '\t')
			ft_printf("Parsing: %u: isn't readable\n", line_amount);
		ft_memdel((void**)&line);
		line_amount++;
	}
	if (ret == -1 || (scene->light_amount == 0 && scene->shapes_amount == 0))
		return (FAILED);
	return (GOOD);
}
