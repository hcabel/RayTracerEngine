/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:38:32 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 13:31:15 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	parse_map(t_scene *scene, int fd, char *path)
{
	if (parse_component_amount(scene, fd))
		return (FAILED);
	if (create_object_list(scene)
		|| create_light_list(scene))
		return (MALLOC_ERROR);
	if (close(fd) == -1)
		return (UNKNOWN_ERROR);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (FAILED);
	if (parse_components(scene, fd))
		return (FAILED);
	return (GOOD);
}

int			parsing(t_scene *scene, char *path)
{
	int	fd;
	int	code;

	ft_printf("{y}");
	initcam(&scene->cam);
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		if ((code = parse_map(scene, fd, path) != GOOD))
		{
			if (code == FAILED)
				ft_printf("Parsing: file reading failed\n");
			else
				return (code);
		}
	}
	else if (path != NULL)
		ft_printf("Parsing: file reading failed\n");
	ft_printf("{/}");
	close(fd);
	return (GOOD);
}
