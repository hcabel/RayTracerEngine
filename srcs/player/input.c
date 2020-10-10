/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:19:18 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 18:29:27 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	hook_event(t_bool *quit, t_info *info)
{
	SDL_Event	event;

	info->scene.cam.forward.z = cos(info->scene.cam.rotation.x) *
		cos(info->scene.cam.rotation.y);
	info->scene.cam.forward.x = cos(info->scene.cam.rotation.x) *
		sin(info->scene.cam.rotation.y);
	info->scene.cam.forward.y = -sin(info->scene.cam.rotation.x);

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		quit->bool = 1;
	else if (event.type == SDL_KEYDOWN)
		keyboard_input(quit, info, &event);
	else if (event.type == SDL_MOUSEBUTTONDOWN)
		mouse_press_input(quit, info, &event);
	else if (event.type == SDL_MOUSEMOTION)
		mouse_move_input(quit, info, &event);
}
