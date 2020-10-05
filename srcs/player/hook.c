/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:19:18 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 18:40:18 by hcabel           ###   ########.fr       */
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
		info->scene.cam.forward.z = cos(info->scene.cam.rotation.x) * cos(info->scene.cam.rotation.y);
		info->scene.cam.forward.x = cos(info->scene.cam.rotation.x) * sin(info->scene.cam.rotation.y);
		info->scene.cam.forward.y = -sin(info->scene.cam.rotation.x);

		info->scene.shapes[0].location = vector_add(info->scene.cam.location, vector_mult(info->scene.cam.forward, 10));
		info->scene.shapes[0].scale = new_vector(.1,.1,.1);
		if (event.key.keysym.sym == SDLK_ESCAPE)
			quit->bool = 1;
		else if (event.key.keysym.sym == SDLK_w)
			info->scene.cam.location = vector_add(info->scene.cam.location, vector_mult(info->scene.cam.forward, 1));
		else if (event.key.keysym.sym == SDLK_s)
			info->scene.cam.location = vector_add(info->scene.cam.location, vector_mult(info->scene.cam.forward, -1));
		else if (event.key.keysym.sym == SDLK_a)
			info->scene.cam.location.x -= 0.5;
		else if (event.key.keysym.sym == SDLK_d)
			info->scene.cam.location.x += 0.5;
		else if (event.key.keysym.sym == SDLK_SPACE)
			info->scene.cam.location.y -= 0.5;
		else if (event.key.keysym.sym == SDLK_LCTRL)
			info->scene.cam.location.y += 0.5;
		else if (event.key.keysym.sym == SDLK_KP_4)
			info->scene.cam.rotation.y -= 0.1;
		else if (event.key.keysym.sym == SDLK_KP_6)
			info->scene.cam.rotation.y += 0.1;
		else if (event.key.keysym.sym == SDLK_KP_8)
			info->scene.cam.rotation.x += 0.1;
		else if (event.key.keysym.sym == SDLK_KP_2)
			info->scene.cam.rotation.x -= 0.1;
		else if (event.key.keysym.sym == SDLK_UP
			&& info->screen.resolution > 1)
			info->screen.resolution -= 1;
		else if (event.key.keysym.sym == SDLK_DOWN)
			info->screen.resolution += 1;
		/*printf("	Cam location : {%.2f %.2f %.2f}\n",
			info->scene.cam.location.x, info->scene.cam.location.y, info->scene.cam.location.z);
		printf("	Cam forward : {%.2f %.2f %.2f}\n",
			info->scene.cam.forward.x, info->scene.cam.forward.y, info->scene.cam.forward.z);
		printf("	Cam rotation : {%.2f %.2f}\n",
			info->scene.cam.rotation.x, info->scene.cam.rotation.y);*/

		//info->screen.resolution = FIRST_RESOLUTION;
		draw_calls_add(info, UPDATE_VIEWPORT);
	}
}
