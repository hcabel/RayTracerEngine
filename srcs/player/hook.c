/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:19:18 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/01 18:41:56 by hcabel           ###   ########.fr       */
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
			info->scene.cam.location.z -= 0.5;
		else if (event.key.keysym.sym == SDLK_s)
			info->scene.cam.location.z += 0.5;
		else if (event.key.keysym.sym == SDLK_a)
			info->scene.cam.location.x -= 0.5;
		else if (event.key.keysym.sym == SDLK_d)
			info->scene.cam.location.x += 0.5;
		else if (event.key.keysym.sym == SDLK_SPACE)
			info->scene.cam.location.y -= 0.5;
		else if (event.key.keysym.sym == SDLK_LSHIFT)
			info->scene.cam.location.y += 0.5;
		else if (event.key.keysym.sym == SDLK_UP
			&& info->screen.resolution > 1)
			info->screen.resolution /= 2;
		else if (event.key.keysym.sym == SDLK_DOWN)
			info->screen.resolution *= 2;
		printf("Cam location : {%.2f %.2f %.2f}\n",
			info->scene.cam.location.x, info->scene.cam.location.y, info->scene.cam.location.z);
		//info->screen.resolution = FIRST_RESOLUTION;
		draw_calls_add(info, UPDATE_VIEWPORT);
	}
}
