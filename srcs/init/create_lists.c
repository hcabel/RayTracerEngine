/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 11:37:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 13:13:27 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		create_object_list(t_scene *scene)
{
	unsigned int	i;

	scene->shapes = malloc(sizeof(t_object) * (scene->shapes_amount + 1));
	if (scene->shapes == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (i < scene->shapes_amount)
	{
		initobject(&scene->shapes[i]);
		i++;
	}
	return (GOOD);
}

int		create_light_list(t_scene *scene)
{
	unsigned int	i;

	scene->lights = malloc(sizeof(t_light) * (scene->light_amount + 1));
	if (scene->lights == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (i < scene->light_amount)
	{
		initlight(&scene->lights[i]);
		i++;
	}
	return (GOOD);
}
