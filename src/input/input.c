/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:58:57 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:31:15 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	mouse_event(t_info *info, SDL_Event *event)
{
	int	code;

	if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		info->mouse.down = 1;
		if ((code = mouse_press(info)) != GOOD)
			return (code);
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		if (info->mouse.down == 1)
			info->mouse.dragged = 1;
		mouse_move(info, event);
	}
	else if (event->type == SDL_MOUSEWHEEL)
	{
		info->mouse.dragged = 0;
		mouse_wheel(info, event);
	}
	return (GOOD);
}

int			hook_event(int *quit, t_info *info)
{
	SDL_Event	event;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		*quit = 1;
	else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		keyboard_press(quit, info, &event);
	else if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEMOTION
		|| event.type == SDL_MOUSEWHEEL || event.type == SDL_MOUSEBUTTONDOWN)
		return (mouse_event(info, &event));
	else if (event.type == SDL_WINDOWEVENT
		&& event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		return (resize_window(info));
	return (GOOD);
}
