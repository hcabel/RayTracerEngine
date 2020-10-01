/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:12:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/01 17:02:29 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			create_thread_to_calculate_new_frame(t_info *info)
{
	pthread_t		thread_list[RAYMARCHING_THREAD];
	t_thread		thread_infos[RAYMARCHING_THREAD];
	unsigned int	i;

	i = 0;
	while (i < RAYMARCHING_THREAD)
	{
		thread_infos[i].start_index = i;
		thread_infos[i].screen = &info->screen;
		thread_infos[i].scene = &info->scene;
		pthread_create(&(thread_list[i]), NULL, thread_calculs_functions, &(thread_infos[i]));
		i++;
	}
	i = 0;
	while (i < RAYMARCHING_THREAD)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
}

void				new_viewport_frame(t_info *info)
{
	Uint32 tick = SDL_GetTicks();
	ft_printf("[DrawCall] Viewport...	");
	info->screen.viewport_image.w = info->screen.viewport_area.w / info->screen.resolution;
	info->screen.viewport_image.h = info->screen.viewport_area.h / info->screen.resolution;
	SDL_LockTexture(info->screen.tex, &info->screen.viewport_image, &info->screen.pixels, &info->screen.pitch);

	create_thread_to_calculate_new_frame(info);

	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex,
		&info->screen.viewport_image, &info->screen.viewport_area);
	SDL_RenderPresent(info->renderer);
	printf("End (%.2f)\n", (double)(SDL_GetTicks() - tick) / 100);
}
