/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 16:22:48 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 20:00:51 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	verif_light_type(char *line)
{
	if (ft_strncmp("point]", line, 7) == GOOD)
		return (GOOD);
	return (PARSING_ERROR);
}

static int	verif_object_type(char *line)
{
	if (ft_strncmp("sphere]", line, 8) == GOOD)
		return (GOOD);
	return (PARSING_ERROR);
}

int			parse_component_amount(t_scene *scene, int fd)
{
	char		*line;
	int			ret;
	int			line_amount;

	line_amount = 0;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		line_amount++;
		if (line[0] && line[0] == '[')
		{
			if (ft_strncmp("[object:", line, 8) == GOOD)
			{
				if (verif_object_type(line + 8) == GOOD)
					scene->shapes_amount++;
				else
					ft_printf("{y}Parsing : Line %d object type doesn't exit\n{/}", line_amount);
			}
			else if (ft_strncmp("[light:", line, 7) == GOOD)
			{
				if (verif_light_type(line + 7) == GOOD)
					scene->light_amount++;
				else
					ft_printf("{y}Parsing : Line %d Light type doesn't exit\n{/}", line_amount);
			}
		}
		free(line);
	}
	return (ret == -1 ? PARSING_ERROR : GOOD);
}
