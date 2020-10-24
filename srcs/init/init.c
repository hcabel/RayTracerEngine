/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:42:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/24 14:05:18 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	init_sdl(t_info *info)
{
	if (SDL_Init(SDL_INIT_VIDEO) != GOOD )
		return (SDL_ERROR);
	if (!(info->window = SDL_CreateWindow(WINDOW_NAME, 0, 0, WIN_WIDTH,
		WIN_HEIGTH, SDL_WINDOW_SHOWN)))
		return (SDL_ERROR);
	if (!(info->renderer = SDL_CreateRenderer(info->window,
		-1, SDL_RENDERER_ACCELERATED)))
		return (SDL_ERROR);
	if (!(info->screen.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		WIN_WIDTH, WIN_HEIGTH)))
		return (SDL_ERROR);
	if (!(info->screen.viewport.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		WIN_WIDTH, WIN_HEIGTH)))
		return (SDL_ERROR);
	return(GOOD);
}

static int	init_info_structure(t_info *info)
{
	info->scene.light_amount = 0;
	info->scene.shapes_amount = 0;
	draw_calls_clear_list(info);
	info->update_function_list[0] = DRAWCALL_DETAILS_PANEL;
	info->update_function_list[1] = DRAWCALL_VIEWMODE_PANEL;
	info->update_function_list[2] = DRAWCALL_VIEWPORT;
	pthread_mutex_init(&info->screen.viewport.sampling.mutex, NULL);
	info->screen.viewport.sampling.threads_end_status =
		powf(2, RAYMARCHING_THREAD) - 1;
	info->screen.viewport.sampling.threads_status =
		info->screen.viewport.sampling.threads_end_status;
	info->screen.viewport.resolution = FIRST_RESOLUTION;
	info->scene.cam.forward.x = cos(info->scene.cam.rotation.x) *
		cos(info->scene.cam.rotation.y);
	info->scene.cam.forward.y = cos(info->scene.cam.rotation.x) *
		sin(info->scene.cam.rotation.y);
	info->scene.cam.forward.z = sin(info->scene.cam.rotation.x);
	info->scene.cam.viewmode = 0;
	info->scene.target = NULL;
	info->scene.target_type = 0;
	info->screen.viewport.sampling.kill_thread.bool = 0;
	return (GOOD);
}

int			init(t_info *info, char *argv)
{
	int	code_error;

	init_info_structure(info);
	if ((code_error = init_sdl(info)))
		return (code_error);
	if ((code_error = init_interfaces(&info->screen)))
		return (code_error);
	if (load_interface_images(info->renderer, &info->screen) != GOOD)
	{
		ft_printf("{r}ERROR LOAD IMAGE\n{/}");
	}
	if ((code_error = parsing(&info->scene, argv)))
		return (code_error);
	return(GOOD);
}
