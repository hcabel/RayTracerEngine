/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:23:15 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 12:44:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <unistd.h>

static int	create_object_list(t_scene *scene)
{
	unsigned int	i;

	scene->shapes = malloc(sizeof(t_object) * scene->shapes_amount);
	if (scene->shapes == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (i < scene->shapes_amount)
	{
		scene->shapes[i] = new_object();
		i++;
	}
	return (GOOD);
}

static int	create_light_list(t_scene *scene)
{
	unsigned int	i;

	scene->lights = malloc(sizeof(t_light) * scene->light_amount);
	if (scene->lights == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (i < scene->light_amount)
	{
		scene->lights[i] = new_light();
		i++;
	}
	return (GOOD);
}

static int	create_default_scene(t_scene *scene)
{
	ft_printf("{y}		Create default scene\n{/}");
	if ((scene->lights = malloc(sizeof(t_light) * 1)) == NULL)
		return (MALLOC_ERROR);
	if ((scene->shapes = malloc(sizeof(t_object) * 2)) == NULL)
		return (MALLOC_ERROR);
	scene->shapes_amount = 2;
	scene->light_amount = 1;
	scene->shapes[0] = new_object();
	scene->shapes[0].scale = new_vector(10, 10, 10);
	scene->shapes[0].color = new_vector(50, 200, 200);
	scene->shapes[1] = new_object();
	scene->shapes[1].scale = new_vector(500, 500, 500);
	scene->shapes[1].color = new_vector(200, 50, 200);
	scene->shapes[1].location = new_vector(0, -25, 0);
	scene->shapes[1].sdf_index = 4;
	scene->lights[0].location = new_vector(0, 50, 0);
	scene->cam.location = new_vector(0, -10, -75);
	scene->cam.viewmode = GAME_VIEWMODE;
	return (GOOD);
}

static int	parse_map(t_scene *scene, int fd, char *path)
{
	if (parsing_header(scene, fd))
		return (FAILED);
	if (create_object_list(scene) || create_light_list(scene))
		return (MALLOC_ERROR);
	if (parse_components(scene, fd))
		return (FAILED);
	return (GOOD);
}

int			parsing(t_scene *scene, char *path)
{
	int	fd;
	int	code;

	ft_printf("{g}	Parsing\n{/}");
	scene->cam = new_cam();
	scene->cam.viewmode = EDITOR_VIEWMODE;
	if (!path)
		return (create_default_scene(scene));
	fd = open(path, O_RDONLY);
	if (fd == -1 || (code = parse_map(scene, fd, path)) != GOOD)
	{
		if (fd == -1 || code == FAILED)
		{
			if (fd == -1)
				ft_printf("{y}		Error file does not exit\n");
			else
				ft_printf("{y}		Error: file reading failed !\n{/}");
			create_default_scene(scene);
		}
		else
			ft_printf("{r}		%s!\n{/}", error_to_str(code));
	}
	close(fd);
	ft_printf("{g}	End\n{/}");
	return (GOOD);
}
