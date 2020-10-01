/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:19:18 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/01 17:12:05 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	hook_event(t_bool *quit, t_info *info)
{
	SDL_Event	event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		quit->bool = 1;
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			quit->bool = 1;
		else if (event.key.keysym.sym == SDLK_w)
			info->scene.cam.location.z += 1;
		else if (event.key.keysym.sym == SDLK_s)
			info->scene.cam.location.z -= 1;
		else if (event.key.keysym.sym == SDLK_a)
			info->scene.cam.location.x -= 1;
		else if (event.key.keysym.sym == SDLK_d)
			info->scene.cam.location.x += 1;
		else if (event.key.keysym.sym == SDLK_SPACE)
			info->scene.cam.location.y -= 1;
		else if (event.key.keysym.sym == SDLK_LSHIFT)
			info->scene.cam.location.y += 1;
		else if (event.key.keysym.sym == SDLK_UP
			&& info->screen.resolution > 1)
			info->screen.resolution /= 2;
		else if (event.key.keysym.sym == SDLK_DOWN)
			info->screen.resolution *= 2;
		//info->screen.resolution = FIRST_RESOLUTION;
		draw_calls_add(info, UPDATE_VIEWPORT);
	}
}
