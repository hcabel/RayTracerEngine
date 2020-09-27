/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:42:47 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 22:00:57 by hcabel           ###   ########.fr       */
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
	return(GOOD);
}

static int	init_info_structure(t_info *info)
{
	info->scene.light_amount = 0;
	info->scene.shapes_amount = 0;
	info->update_function_list[0] = UPDATE_VIEWPORT;
	return (GOOD);
}

#include <stdio.h>

int			init(t_info *info, char *argv)
{
	int	code_error;

	init_info_structure(info);
	if ((code_error = init_sdl(info)))
		return (code_error);
	if ((code_error = parsing(&info->scene, argv)))
		return (code_error);
	// DEBUG *****************************************
	for (unsigned int i = 0; i < info->scene.shapes_amount; i++)
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
	ft_printf("{/}\n");
	// END *******************************************
	return(GOOD);
}
