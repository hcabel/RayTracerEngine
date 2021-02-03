/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_wheel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 12:16:06 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/02 13:52:51 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	wheel_scroll_left(t_top_panel *panel, int dir)
{
	if (panel->viewmode.current <= 0)
		return (0);
	panel->viewmode.current += dir;
	if (panel->viewmode.current < 0)
		panel->viewmode.current = 0;
	panel->viewmode.scrollbar.button.area.x =
		round(panel->viewmode.current
		* (float)panel->viewmode.scrollbar.ratio);
	return (2);
}

static int	wheel_scroll_right(t_top_panel *panel, int dir)
{
	unsigned int	max;

	printf("right\n");
	max = (panel->viewmode.scrollbar.max) - panel->viewmode.area.w;
	if (panel->viewmode.current >= max)
		return (0);
	panel->viewmode.current += dir;
	if (panel->viewmode.current > max)
		panel->viewmode.current = max;
	panel->viewmode.scrollbar.button.area.x =
		round(panel->viewmode.current
		* (float)panel->viewmode.scrollbar.ratio);
	return (2);
}

static int	wheel_on_top_panel(t_top_panel *panel, t_vector2d cursorlocation,
				int dir)
{
	if (aabb(panel->viewmode.area, cursorlocation) == GOOD)
	{
		if (dir < 0)
			return (wheel_scroll_left(panel, dir));
		else if (dir > 0)
			return (wheel_scroll_right(panel, dir));
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
	set_multiple_drawcall_from_code(result, info);
}
