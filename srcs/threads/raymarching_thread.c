/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:12:01 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/10 11:59:26 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				*thread_calculs_functions(void *p)
{
	t_thread		*thread_info;
	t_info			*info;
	t_vector2d		co;
	unsigned int	i;

	thread_info = p;
	info = thread_info->info;
	i = thread_info->start_index;
	while (i < (unsigned int)info->screen.viewport.image.w *
		(unsigned int)info->screen.viewport.image.h)
	{
		co = get_pixel_coordinates(i, info->screen.viewport.image.w);
		((unsigned int*)info->screen.viewport.pixels)[(int)co.x +
			((int)co.y * WIN_WIDTH)] = raymarching(&info->scene,
			get_ray_direction_from_coordinate(co, &info->scene.cam,
			info->screen.viewport.image.w, info->screen.viewport.image.h));
		i += RAYMARCHING_THREAD;
	}
	while (pthread_mutex_trylock(&info->sampling.mutex))
		;
	info->sampling.threads_status |= 1 << thread_info->start_index;
	pthread_mutex_unlock(&info->sampling.mutex);
	pthread_exit(NULL);
	return ((void*)0);
}
