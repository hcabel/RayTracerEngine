/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_panel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:12:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/12 12:31:39 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			on_gpu(t_info *info)
{
	ft_printf("{y}Start\n{/}");
	calculate_image_with_cg(info);
	ft_printf("{y}END\n{/}");
	SDL_UnlockTexture(info->screen.viewport.tex);
	SDL_RenderCopy(info->renderer, info->screen.viewport.tex,
		&info->screen.viewport.image, &info->screen.viewport.area);
	SDL_RenderPresent(info->renderer);
	ft_printf("{y}EEND\n{/}");
}

static void			on_cpu(t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < RAYMARCHING_THREAD)
	{
		info->screen.viewport.sampling.threads_infos[i].start_index = i;
		info->screen.viewport.sampling.threads_infos[i].info = info;
		pthread_create(&(info->screen.viewport.sampling.threads[i]), NULL,
			thread_calculs_functions,
			&(info->screen.viewport.sampling.threads_infos[i]));
		i++;
	}
	draw_calls_add(info, DRAWCALL_CHECK_VIEWPORT);
}

void				new_viewport_frame(t_info *info)
{
	if (!ONGPU)
		if (info->screen.viewport.sampling.threads_status !=
			info->screen.viewport.sampling.threads_end_status)
			kill_all_thread(&info->screen.viewport.sampling);
	info->screen.viewport.resolution = 1;
	ft_printf("[DrawCall] Viewport (sampling %3d)\n",
		info->screen.viewport.resolution);
	info->screen.viewport.sampling.threads_status = 0;
	info->screen.viewport.image.w = info->screen.viewport.area.w
		/ info->screen.viewport.resolution;
	info->screen.viewport.image.h = info->screen.viewport.area.h
		/ info->screen.viewport.resolution;
	SDL_LockTexture(info->screen.viewport.tex, &info->screen.viewport.image,
		&info->screen.viewport.pixels, &info->screen.pitch);
	if (ONGPU)
		on_gpu(info);
	else
		on_cpu(info);
}

void				check_viewport_render(t_info *info)
{
	while (pthread_mutex_trylock(&info->screen.viewport.sampling.mutex))
		;
	if (info->screen.viewport.sampling.threads_status ==
		info->screen.viewport.sampling.threads_end_status)
	{
		SDL_UnlockTexture(info->screen.viewport.tex);
		SDL_RenderCopy(info->renderer, info->screen.viewport.tex,
			&info->screen.viewport.image, &info->screen.viewport.area);
		SDL_RenderPresent(info->renderer);
		if (info->screen.viewport.resolution > 1)
		{
			if (info->screen.viewport.resolution > 2)
				info->screen.viewport.resolution -= 2;
			else
				info->screen.viewport.resolution -= 1;
			draw_calls_add(info, DRAWCALL_VIEWPORT);
		}
	}
	else
		draw_calls_add(info, DRAWCALL_CHECK_VIEWPORT);
	pthread_mutex_unlock(&info->screen.viewport.sampling.mutex);
}
