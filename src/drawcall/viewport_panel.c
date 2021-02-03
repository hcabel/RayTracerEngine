/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_panel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:09:48 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 13:10:40 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	low_resolution(t_info *info)
{
	if (info->screen.viewport.resolution > 1)
	{
		if (info->screen.viewport.resolution > 2)
			info->screen.viewport.resolution -= 2;
		else
			info->screen.viewport.resolution -= 1;
		drawcall_add(info, DRAWCALL_VIEWPORT);
	}
}

static int	on_gpu(t_info *info)
{
	int	code;

	SDL_LockTexture(info->screen.viewport.tex, &info->screen.viewport.image,
		&info->screen.viewport.pixels, &info->screen.pitch);
	if ((code = calculate_image_with_cg(info)) != GOOD)
		return (code);
	SDL_UnlockTexture(info->screen.viewport.tex);
	SDL_RenderCopy(info->renderer, info->screen.viewport.tex,
		&info->screen.viewport.image, &info->screen.viewport.area);
	SDL_RenderPresent(info->renderer);
	low_resolution(info);
	return (GOOD);
}

static void	on_cpu(t_info *info)
{
	unsigned int	i;

	return ;
	SDL_LockTexture(info->screen.viewport.tex, &info->screen.viewport.image,
		&info->screen.viewport.pixels, &info->screen.pitch);
	i = 0;
	while (i < RAYMARCHING_THREAD)
	{
		info->screen.viewport.sampling.threads_infos[i].start_index = i;
		info->screen.viewport.sampling.threads_infos[i].info = info;
		pthread_create(&(info->screen.viewport.sampling.threads[i]),
			NULL, thread_calculs_functions,
			&(info->screen.viewport.sampling.threads_infos[i]));
		i++;
	}
	drawcall_add(info, DRAWCALL_CHECK_VIEWPORT);
}

int			drawcall_viewport(t_info *info)
{
	int	code;

	if (!info->ongpu)
		kill_all_thread(&info->screen.viewport.sampling);
	info->screen.viewport.sampling.threads_status = 0;
	ft_printf("[DrawCall] Viewport (%s sampling %3d)\n",
		(info->ongpu == 1 ? "GPU" : "CPU"), info->screen.viewport.resolution);
	info->screen.viewport.image.w = info->screen.viewport.area.w
		/ info->screen.viewport.resolution;
	info->screen.viewport.image.h = info->screen.viewport.area.h
		/ info->screen.viewport.resolution;
	if (info->ongpu)
	{
		if ((code = on_gpu(info)) != GOOD)
			return (code);
	}
	else
		on_cpu(info);
	return (GOOD);
}

int			drawcall_check_viewport(t_info *info)
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
		low_resolution(info);
	}
	else
		drawcall_add(info, DRAWCALL_CHECK_VIEWPORT);
	pthread_mutex_unlock(&info->screen.viewport.sampling.mutex);
	return (GOOD);
}
