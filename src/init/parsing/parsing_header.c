/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:15:22 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/05 11:53:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_attributes(t_scene *scene, char *line,
				unsigned int line_amount)
{
	if (ft_strncmp("shapes: ", line, 8) == GOOD)
		scene->shapes_amount = ft_atoi(line + 8);
	else if (ft_strncmp("lights: ", line, 8) == GOOD)
		scene->light_amount = ft_atoi(line + 8);
	else
		ft_printf("{y}		Error: %d{/}\n", line_amount);
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
		if (line_amount == 1 && ft_strncmp("[header]", line, 8) != GOOD)
		{
			ft_memdel((void**)&line);
			return (PARSING_NO_HEADER);
		}
		else if (line[0] == '\t')
			parse_attributes(scene, line + 1, line_amount);
		else if (ft_strncmp("[body]", line, 8) == GOOD)
		{
			ft_memdel((void**)&line);
			break ;
		}
		line_amount++;
		ft_memdel((void**)&line);
	}
	return (ret != 1 || (scene->light_amount == 0 && scene->shapes_amount == 0)
		? FAILED : GOOD);
}
