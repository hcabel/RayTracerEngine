/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/10 12:24:50 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	witch_viewmode_button_hovered(t_vector2d loc,
	t_viewmode_panel *viewmode)
{
	unsigned int	i;
	int				result;

	loc.x -= viewmode->area.x;
	loc.y -= viewmode->area.y;
	i = 0;
	result = FAILED;
	while (i < viewmode->scrollbox.amount)
	{
		if (aabb(viewmode->scrollbox.list[i].area, loc) == GOOD)
		{
			if (viewmode->scrollbox.list[i].ishover.bool != 1)
				result = GOOD;
			viewmode->scrollbox.list[i].ishover.bool = 1;
		}
		else if (viewmode->scrollbox.list[i].ishover.bool == 1)
		{
			viewmode->scrollbox.list[i].ishover.bool = 0;
			result = GOOD;
		}
		i++;
	}
	return (result);
}

static int	witch_details_sector_button_hovered(t_vector2d loc,
				t_selector *selector)
{
	int	result;

	loc.x -= selector->area.x;
	loc.y -= selector->area.y;
	result = FAILED;
	if (aabb(selector->b_left.area, loc) == GOOD)
	{
		if (selector->b_left.ishover.bool != 1)
			result = GOOD;
		selector->b_left.ishover.bool = 1;
	}
	else if (selector->b_left.ishover.bool == 1)
	{
		selector->b_left.ishover.bool = 0;
		result = GOOD;
	}
	if (aabb(selector->b_right.area, loc) == GOOD)
	{
		if (selector->b_right.ishover.bool != 1)
			result = GOOD;
		selector->b_right.ishover.bool = 1;
	}
	else if (selector->b_right.ishover.bool == 1)
	{
		selector->b_right.ishover.bool = 0;
		result = GOOD;
	}
	return (result);
}

static int	witch_details_button_hovered(t_vector2d loc,
	t_details_panel *details)
{
	int	result;

	loc.x -= details->area.x;
	loc.y -= details->area.y;
	result = witch_details_sector_button_hovered(loc, &details->shape_selector);
	if (aabb(details->addcomponent.area, loc) == GOOD)
	{
		if (details->addcomponent.ishover.bool != 1)
			result = GOOD;
		details->addcomponent.ishover.bool = 1;
	}
	else if (details->addcomponent.ishover.bool == 1)
	{
		details->addcomponent.ishover.bool = 0;
		result = GOOD;
	}
	return (result);
}

static void	witch_panel_hovered(t_vector2d loc, t_info *info)
{
	if (aabb(info->screen.viewmode.area, loc) == GOOD)
	{
		if (witch_viewmode_button_hovered(loc, &info->screen.viewmode) == GOOD)
			draw_calls_add(info, DRAWCALL_VIEWMODE_PANEL);
	}
	if (aabb(info->screen.details.area, loc) == GOOD)
	{
		if (witch_details_button_hovered(loc, &info->screen.details) == GOOD)
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
