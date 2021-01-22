/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:15:22 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/22 20:23:56 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	parse_attributes(t_scene *scene, char *line)
{
	if (ft_strncmp("shapes: ", line, 8) == GOOD)
		scene->shapes_amount = ft_atoi(line + 8);
	else if (ft_strncmp("lights: ", line, 8) == GOOD)
		scene->light_amount = ft_atoi(line + 8);
	else
		return (FAILED);
	return (GOOD);
}

int			parsing_header(t_scene *scene, int fd)
{
	char			*line;
	int				ret;
	unsigned int	line_amount;

	line_amount = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		line = ft_strtolower(line);
		if (line_amount == 1)
		{
			if (ft_strncmp("[header]", line, 8) != GOOD)
				return (FAILED);
		}
		else if (line[0] == '\t')
		{
			if (parse_attributes(scene, line + 1) != GOOD)
				ft_printf("		{y}Error: %d{/}\n", line_amount);
		}
		else if (ft_strncmp("[body]", line, 8) == GOOD)
			break ;
		ft_memdel((void**)&line);
		line_amount++;
	}
	if (ret != 1 || (scene->light_amount == 0 && scene->shapes_amount == 0))
		return (FAILED);
	return (GOOD);
}