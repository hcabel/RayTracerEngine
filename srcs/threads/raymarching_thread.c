/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:12:01 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/12 11:36:08 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_thread_is_finish(t_info *info, t_thread *thread_info)
{
	while (pthread_mutex_trylock(&info->screen.viewport.sampling.mutex))
		;
	info->screen.viewport.sampling.threads_status |=
		1 << thread_info->start_index;
	pthread_mutex_unlock(&info->screen.viewport.sampling.mutex);
}

static void	calcule_for_each_pixel(t_info *info, t_thread *thread_info,
				unsigned int i)
{
	t_vector2d	coordinates;
	t_vector	dir;

	coordinates = get_pixel_coordinates(i, info->screen.viewport.image.w);
	dir = get_ray_direction(coordinates, info->scene.cam.rotation, 90,
		info->screen.viewport.image);
	((unsigned int*)info->screen.viewport.pixels)[(int)coordinates.x +
		((int)coordinates.y * WIN_WIDTH)] = raymarching(&info->scene, dir);
}

void		*thread_calculs_functions(void *p)
{
	t_thread		*thread_info;
	t_info			*info;
	unsigned int	i;

	thread_info = p;
	info = thread_info->info;
	i = thread_info->start_index;
	while (i < (unsigned int)info->screen.viewport.image.w *
		(unsigned int)info->screen.viewport.image.h)
	{
		if (info->screen.viewport.sampling.kill_thread.bool == 1)
		{
			set_thread_is_finish(info, thread_info);
			pthread_exit(NULL);
			return ((void*)0);
		}
		calcule_for_each_pixel(info, thread_info, i);
		i += RAYMARCHING_THREAD;
	}
	set_thread_is_finish(info, thread_info);
	pthread_exit(NULL);
	return ((void*)0);
}
