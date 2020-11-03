/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/03 14:46:20 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	witch_panel_hovered(t_vector2d loc, t_info *info)
{
	if (aabb(info->screen.viewmode.area, loc) == GOOD)
		if (move_on_viewmode_panel(loc, &info->screen.viewmode) == GOOD)
			draw_calls_add(info, DRAWCALL_VIEWMODE_PANEL);
	if (aabb(info->screen.details.area, loc) == GOOD)
		if (move_on_details_panel(loc, &info->screen.details) == GOOD)
			draw_calls_add(info, DRAWCALL_DETAILS_PANEL);
}

void		mouse_move_input(t_bool *quit, t_info *info, SDL_Event *event)
{
	int			updateviewport;
	t_vector2d	mouse_location;
	float		tmp;
	t_object	*obj;

	mouse_location.x = event->motion.x;
	mouse_location.y = event->motion.y;
	updateviewport = FAILED;
	if (info->mouse.is_dragged.bool == 1
		&& info->scene.target != NULL)
	{
		obj = (t_object*)info->scene.target;
		if (info->scene.transphorm_axis == 'x')
		{
			tmp = info->mouse.target_base_3dvector.x
				+ (mouse_location.x - info->mouse.startloc.x) / 10;
			if (obj->location.x != tmp)
			{
				obj->location.x = tmp;
				updateviewport = GOOD;
			}
		}
		else if (info->scene.transphorm_axis == 'y')
		{
			tmp = info->mouse.target_base_3dvector.y
				+ (info->mouse.startloc.y - mouse_location.y) / 10;
			if (obj->location.y != tmp)
			{
				obj->location.y = tmp;
				updateviewport = GOOD;
			}
		}
		else if (info->scene.transphorm_axis == 'z')
		{
			tmp = info->mouse.target_base_3dvector.z
				+ (info->mouse.startloc.x - mouse_location.x) / 10;
			if (obj->location.z != tmp)
			{
				obj->location.z = tmp;
				updateviewport = GOOD;
			}
		}
	}
	else
		witch_panel_hovered(mouse_location, info);
	if (updateviewport == GOOD)
	{
		info->screen.viewport.resolution = FIRST_RESOLUTION;
		draw_calls_add(info, DRAWCALL_VIEWPORT);
		info->screen.details.skip_selector_preview.bool = 1;
		draw_calls_add(info, DRAWCALL_DETAILS_PANEL);
	}
}
