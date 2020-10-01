/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:42:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/01 16:42:17 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	init_sdl(t_info *info)
{
	if (SDL_Init(SDL_INIT_VIDEO) != GOOD )
		return (SDL_ERROR);
	if (!(info->window = SDL_CreateWindow(WINDOW_NAME,SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGTH, SDL_WINDOW_SHOWN)))
		return (SDL_ERROR);
	if (!(info->renderer = SDL_CreateRenderer(info->window,
		-1, SDL_RENDERER_ACCELERATED)))
		return (SDL_ERROR);
	if (!(info->screen.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		WIN_WIDTH, WIN_HEIGTH)))
		return (SDL_ERROR);
	info->screen.viewport_area.x = 200;
	info->screen.viewport_area.y = 0;
	info->screen.viewport_area.w = WIN_WIDTH - info->screen.viewport_area.x;
	info->screen.viewport_area.h = WIN_HEIGTH;
	info->screen.viewport_image.x = info->screen.viewport_area.x;
	info->screen.viewport_image.y = info->screen.viewport_area.y;
	info->screen.hud.x = 0;
	info->screen.hud.y = 0;
	info->screen.hud.w = info->screen.viewport_area.x;
	info->screen.hud.h = WIN_HEIGTH;
	return(GOOD);
}

static int	init_info_structure(t_info *info)
{
	info->scene.light_amount = 0;
	info->scene.shapes_amount = 0;
	draw_calls_clear_list(info);
	info->update_function_list[1] = UPDATE_VIEWPORT;
	info->update_function_list[0] = UPDATE_HUD;
	info->screen.resolution = FIRST_RESOLUTION;
	return (GOOD);
}

int			init(t_info *info, char *argv)
{
	int	code_error;

	init_info_structure(info);
	if ((code_error = init_sdl(info)))
		return (code_error);
	if ((code_error = parsing(&info->scene, argv)))
		return (code_error);
	// DEBUG *****************************************
	/*for (unsigned int i = 0; i < info->scene.shapes_amount; i++)
	{
		ft_printf("{m}[object:sphere]\n");
		printf("	location: {%.f, %.f, %.f}\n", info->scene.shapes[i].location.x, info->scene.shapes[i].location.y, info->scene.shapes[i].location.z);
		printf("	rotation: {%.f, %.f}\n", info->scene.shapes[i].rotation.x, info->scene.shapes[i].rotation.y);
		printf("	color: {%.f, %.f, %.f}\n", info->scene.shapes[i].color.x, info->scene.shapes[i].color.y, info->scene.shapes[i].color.z);
		printf("	scale: {%.f, %.f, %.f}\n", info->scene.shapes[i].scale.x, info->scene.shapes[i].scale.y, info->scene.shapes[i].scale.z);
	}
	for (unsigned int i = 0; i < info->scene.light_amount; i++)
	{
		ft_printf("{c}[light:point]\n");
		printf("	location: {%.f, %.f, %.f}\n", info->scene.lights[i].location.x, info->scene.lights[i].location.y, info->scene.lights[i].location.z);
		printf("	rotation: {%.f, %.f}\n", info->scene.lights[i].rotation.x, info->scene.lights[i].rotation.y);
		printf("	intensity: %.f\n", info->scene.lights[i].intensity);
	}
	ft_printf("{/}\n");*/
	// END *******************************************
	return(GOOD);
}
