/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/28 12:17:44 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	mouse_move(int *quit, t_info *info, SDL_Event *event)
{
	int	result;

	result = 0;
	info->mouse.location.x = event->motion.x;
	info->mouse.location.y = event->motion.y;
	if (aabb(info->screen.top.area, info->mouse.location) == GOOD)
		result |= move_on_top_panel(&info->screen.top, info->mouse.location);

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
