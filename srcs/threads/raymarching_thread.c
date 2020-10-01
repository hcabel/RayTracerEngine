/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:12:01 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/01 16:42:56 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector		get_ray_direction_from_coordinate(t_vector2d coordinates,
						unsigned int wid, unsigned int height)
{
	t_vector	dir;

	coordinates.x = coordinates.x / wid - 0.5;
	coordinates.y = coordinates.y / height - 0.5;
	dir.y = coordinates.y;
	dir.x = coordinates.x * wid / height;
	dir.z = 1;
	dir = vectornormalize(rotate_y(dir, 0));
	return (dir);
}

static t_vector2d	get_pixel_coordinates(unsigned int i, unsigned int width)
{
	t_vector2d	result;

	result.x = i % width;
	result.y = i / width;
	return (result);
}

void				*thread_calculs_functions(void *p)
{
	t_thread		*thread_info;
	t_scene			*scene;
	t_screen		*screen;
	t_vector2d		co;
	unsigned int	i;

	thread_info = p;
	scene = thread_info->scene;
	screen = thread_info->screen;
	i = thread_info->start_index;
	while (i < (unsigned int)screen->viewport_image.w *
		(unsigned int)screen->viewport_image.h)
	{
		co = get_pixel_coordinates(i, screen->viewport_image.w);
		((unsigned int*)screen->pixels)[(int)co.x + ((int)co.y * WIN_WIDTH)] =
			raymarching(scene, get_ray_direction_from_coordinate(co,
			screen->viewport_image.w, screen->viewport_image.h));
		i += RAYMARCHING_THREAD;
	}
	pthread_exit(NULL);
	return ((void*)0);
}
