/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:04:20 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/02 14:54:35 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	keyboard_press(int *quit, t_info *info, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		*quit = 1;
	else if (event->key.keysym.sym == SDLK_w)
		info->scene.cam.location.z += 0.5;
	else if (event->key.keysym.sym == SDLK_s)
		info->scene.cam.location.z -= 0.5;
	else if (event->key.keysym.sym == SDLK_a)
		info->scene.cam.location.x -= 0.5;
	else if (event->key.keysym.sym == SDLK_d)
		info->scene.cam.location.x += 0.5;
	else if (event->key.keysym.sym == SDLK_c)
		info->scene.cam.location.y -= 0.5;
	else if (event->key.keysym.sym == SDLK_SPACE)
		info->scene.cam.location.y += 0.5;
	else if (event->key.keysym.sym == SDLK_KP_4)
		info->scene.cam.rotation.y += 0.1;
	else if (event->key.keysym.sym == SDLK_KP_6)
		info->scene.cam.rotation.y -= 0.1;
	else if (event->key.keysym.sym == SDLK_KP_8)
		info->scene.cam.rotation.x -= 0.1;
	else if (event->key.keysym.sym == SDLK_KP_2)
		info->scene.cam.rotation.x += 0.1;
	info->screen.viewport.resolution = FIRST_RESOLUTION;
	drawcall_add(info, DRAWCALL_VIEWPORT);
}
