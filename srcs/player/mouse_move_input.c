/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/29 13:17:49 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	witch_panel_hovered(t_vector2d loc, t_info *info)
{
	if (aabb(info->screen.viewmode.area, loc) == GOOD)
	{
		if (move_on_viewmode_panel(loc, &info->screen.viewmode) == GOOD)
			draw_calls_add(info, DRAWCALL_VIEWMODE_PANEL);
	}
	if (aabb(info->screen.details.area, loc) == GOOD)
	{
		if (move_on_details_panel(loc, &info->screen.details) == GOOD)
			draw_calls_add(info, DRAWCALL_DETAILS_PANEL);
	}
}

void		mouse_move_input(t_bool *quit, t_info *info, SDL_Event *event)
{
	int			updateviewport;
	t_vector2d	mouse_location;

	mouse_location.x = event->motion.x;
	mouse_location.y = event->motion.y;
	witch_panel_hovered(mouse_location, info);
}
