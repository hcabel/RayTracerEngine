/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:30:09 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/10 18:34:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	keyboard_input(t_bool *quit, t_info *info, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		quit->bool = 1;
	else if (event->key.keysym.sym == SDLK_w)
		info->scene.cam.location = vector_add(info->scene.cam.location,
			vector_mult(info->scene.cam.forward, 1));
	else if (event->key.keysym.sym == SDLK_s)
		info->scene.cam.location = vector_add(info->scene.cam.location,
			vector_mult(info->scene.cam.forward, -1));
	else if (event->key.keysym.sym == SDLK_a)
		info->scene.cam.location.x -= 0.5;
	else if (event->key.keysym.sym == SDLK_d)
		info->scene.cam.location.x += 0.5;
	else if (event->key.keysym.sym == SDLK_SPACE)
		info->scene.cam.location.y -= 0.5;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		info->scene.cam.location.y += 0.5;
	else if (event->key.keysym.sym == SDLK_KP_4)
		info->scene.cam.rotation.y -= 0.1;
	else if (event->key.keysym.sym == SDLK_KP_6)
		info->scene.cam.rotation.y += 0.1;
	else if (event->key.keysym.sym == SDLK_KP_8)
		info->scene.cam.rotation.x += 0.1;
	else if (event->key.keysym.sym == SDLK_KP_2)
		info->scene.cam.rotation.x -= 0.1;
	info->screen.viewport.resolution = FIRST_RESOLUTION;
	draw_calls_add(info, DRAWCALL_VIEWPORT);
}
