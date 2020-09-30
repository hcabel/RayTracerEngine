/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 22:12:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/30 14:11:13 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector		rotatey(t_vector r, float v)
{
	t_vector	result;

	result.x = r.x * cos(v) + r.z * sin(v);
	result.y = r.y;
	result.z = r.z * cos(v) - r.x * sin(v);
	return (result);
}

static t_vector		get_ray_direction(t_vector2d coordinates, unsigned int wid,
						unsigned int height)
{
	t_vector	dir;

	coordinates.x = coordinates.x / wid - 0.5;
	coordinates.y = coordinates.y / height - 0.5;
	dir.y = coordinates.y;
	dir.x = coordinates.x * wid / height;
	dir.z = 1;
	dir = vectornormalize(rotatey(dir, 0));
	return (dir);
}

static t_vector2d	get_pixel_coordinates(unsigned int i, unsigned int width)
{
	t_vector2d	result;

	result.x = i % width;
	result.y = i / width;
	return (result);
}

static void			*thread_calculs_functions(void *p)
{
	t_thread		*thread_info;
	t_scene			*scene;
	t_screen		*screen;
	t_vector		dir;
	t_vector2d		co;
	unsigned int	i;

	thread_info = (t_thread*)p;
	scene = thread_info->scene;
	screen = thread_info->screen;
	i = thread_info->start_index;
	while (i < (unsigned int)screen->viewport_image.w *
		(unsigned int)screen->viewport_image.h)
	{
		co = get_pixel_coordinates(i, screen->viewport_image.w);
		dir = get_ray_direction(co, screen->viewport_image.w, screen->viewport_image.h);
		((unsigned int*)screen->pixels)[(int)co.x + ((int)co.y * WIN_WIDTH)] = raymarching(scene, dir);
		i += RAYMARCHING_THREAD;
	}
	pthread_exit(NULL);
}

static void			new_viewport_frame(t_info *info)
{
	pthread_t		thread_list[RAYMARCHING_THREAD];
	t_thread		thread_infos[RAYMARCHING_THREAD];
	unsigned int	i;

	ft_printf("[DrawCall] Viewport...	\n");
	Uint32 tick = SDL_GetTicks();
	info->screen.viewport_image.w = info->screen.viewport_area.w / info->screen.resolution;
	info->screen.viewport_image.h = info->screen.viewport_area.h / info->screen.resolution;
	SDL_LockTexture(info->screen.tex, &info->screen.viewport_image, &info->screen.pixels, &info->screen.pitch);

	i = 0;
	while (i < RAYMARCHING_THREAD)
	{
		thread_infos[i].start_index = i;
		thread_infos[i].screen = &info->screen;
		thread_infos[i].scene = &info->scene;
		pthread_create(&(thread_list[i]), NULL, thread_calculs_functions,
			(void*)(&(thread_infos[i])));
		i++;
	}
	i = 0;
	while (i < RAYMARCHING_THREAD)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}

	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex,
		&info->screen.viewport_image, &info->screen.viewport_area);
	SDL_RenderPresent(info->renderer);
	printf("End (%.2lfs)\n", (double)(SDL_GetTicks() - tick) / 1000);
}

void				viewport_frame_updates(t_info *info)
{
	new_viewport_frame(info);
	if (info->screen.resolution > 1)
	{
		info->screen.resolution -= 1;
		viewport_frame_updates(info);
	}
	pthread_exit(NULL);
}
