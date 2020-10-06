/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:12:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 12:16:58 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			create_thread_to_calculate_new_frame(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < RAYMARCHING_THREAD)
	{
		info->sampling.threads_infos[i].start_index = i;
		info->sampling.threads_infos[i].info = info;
		pthread_create(&(info->sampling.threads[i]), NULL,
			thread_calculs_functions, &(info->sampling.threads_infos[i]));
		i++;
	}
}

void				new_viewport_frame(t_info *info)
{
	while (pthread_mutex_trylock(&info->sampling.mutex))
		;
	if (info->sampling.threads_status == powf(2, RAYMARCHING_THREAD) - 1)
		info->sampling.threads_status = 0;
	else
	{
		pthread_mutex_unlock(&info->sampling.mutex);
		draw_calls_add(info, UPDATE_VIEWPORT);
		return ;
	}
	pthread_mutex_unlock(&info->sampling.mutex);
	info->screen.viewport_image.w = info->screen.viewport_area.w / info->screen.resolution;
	info->screen.viewport_image.h = info->screen.viewport_area.h / info->screen.resolution;
	SDL_LockTexture(info->screen.tex, &info->screen.viewport_image, &info->screen.pixels, &info->screen.pitch);

	create_thread_to_calculate_new_frame(info);

	draw_calls_add(info, check_viewport_render);
}

void				check_viewport_render(t_info *info)
{
	while (pthread_mutex_trylock(&info->sampling.mutex))
		;
	if (info->sampling.threads_status == powf(2, RAYMARCHING_THREAD) - 1)
	{
		SDL_UnlockTexture(info->screen.tex);
		SDL_RenderCopy(info->renderer, info->screen.tex,
			&info->screen.viewport_image, &info->screen.viewport_area);
		SDL_RenderPresent(info->renderer);
		if (info->screen.resolution > 2)
		{
			info->screen.resolution -= 2;
			draw_calls_add(info, UPDATE_VIEWPORT);
		}
	}
	else
		draw_calls_add(info, check_viewport_render);
	pthread_mutex_unlock(&info->sampling.mutex);
}
