/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:23:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/26 16:27:43 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <fcntl.h>
#include <unistd.h>

static int	create_object_list(t_scene *scene)
{
	unsigned int	i;

	scene->shapes = malloc(sizeof(t_object) * (scene->shapes_amount + 1));
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

	scene->lights = malloc(sizeof(t_light) * (scene->light_amount + 1));
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
	// TODO
}

static int	parse_map(t_scene *scene, int fd, char *path)
{
	if (parsing_header(scene, fd))
		return (FAILED);
	if (create_object_list(scene)
		|| create_light_list(scene))
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
	if (!path)
		create_default_scene(scene);
	else
	{
		fd = open(path, O_RDONLY);
		if (fd != -1)
		{
			if ((code = parse_map(scene, fd, path)) != GOOD)
			{
				if (code == FAILED)
				{
					ft_printf("{y}		Error: file reading failed !\n{/}");
					create_default_scene(scene);
				}
				else
				{
					ft_printf("{r}		%s!\n{/}", error_to_str(code));
					close(fd);
					return (code);
				}
			}
		}
		else
		{
			ft_printf("{y}		Error file does not exit\n");
			create_default_scene(scene);
		}
		close(fd);
	}
	ft_printf("{g}	End\n{/}");
	return (GOOD);
}
