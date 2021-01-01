/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_wheel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 12:16:06 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/29 11:44:05 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	wheel_on_top_panel(t_top_panel *panel, t_vector2d cursorlocation,
				int dir)
{
	unsigned int	max;

	if (aabb(panel->viewmode.area, cursorlocation) == GOOD)
	{
		if (dir < 0)
		{
			if (panel->viewmode.current <= 0)
				return (0);
			panel->viewmode.current += dir;
			if (panel->viewmode.current < 0)
				panel->viewmode.current = 0;
			panel->viewmode.scrollbar.button.area.x
				= round(panel->viewmode.current * (float)panel->viewmode.scrollbar.ratio);
			return (2);
		}
		else if (dir > 0)
		{
			max = (panel->viewmode.scrollbar.max) - panel->viewmode.area.w;
			if (panel->viewmode.current >= max)
				return (0);
			panel->viewmode.current += dir;
			if (panel->viewmode.current > max)
				panel->viewmode.current = max;
			panel->viewmode.scrollbar.button.area.x
				= round(panel->viewmode.current * (float)panel->viewmode.scrollbar.ratio);
			return (2);
		}
	}
	return (0);
}

void		mouse_wheel(int *quit, t_info *info, SDL_Event *event)
{
	int	result;

	result = 0;

	if (info->screen.top.viewmode.scrollbar.enable && event->wheel.y != 0
		&& aabb(info->screen.top.area, info->mouse.location) == GOOD)
		result |= wheel_on_top_panel(&info->screen.top, info->mouse.location,
			event->wheel.y * 10);

	if (result > 0)
	{
		if ((result & 1) != 0)
			drawcall_add(info, DRAWCALL_VIEWPORT);
		if (((result >> 1) & 1) != 0)
			drawcall_add(info, DRAWCALL_TOP_PANEL);
		if (((result >> 2) & 1) != 0)
			drawcall_add(info, DRAWCALL_LEFT_PANEL);
		if (((result >> 3) & 1) != 0)
			drawcall_add(info, DRAWCALL_CHECK_VIEWPORT);
	}
}