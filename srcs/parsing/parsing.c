/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:38:32 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 19:56:07 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static int	parse_map(t_scene *scene, int fd)
{
	int	code_error;
	if ((code_error = parse_component_amount(scene, fd)))
		return (code_error);
	return (GOOD);
}

int			parsing(t_scene *scene, char *path)
{
	int	fd;

	initcam(&scene->cam);
	fd = open(path, O_RDONLY);
	if (fd != -1)
		return (parse_map(scene, fd));
	return (GOOD);
}
