/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 10:36:06 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	witch_viewmode_button_clicked(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.viewmode_area.x;
	loc.y -= info->screen.viewmode_area.y;
	i = 0;
	while (i < info->screen.viewmode_content.amount)
	{
		if (aabb(info->screen.viewmode_content.list[i].area, loc) == GOOD)
			return (info->screen.viewmode_content.list[i].clicked(info));
		else
			i++;
	}
	return (FAILED);
}

static int	viewport_clicked(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.viewmode_area.x;
	loc.y -= info->screen.viewmode_area.y;
	return (FAILED);
	/*i = 0;
	while (i < info->screen.viewmode_content.amount)
	{
		if (aabb(info->screen.viewmode_content.list[i].area, loc) == GOOD)
		{
			info->screen.viewmode_content.list[i].clicked(info);
		}
		else
		{
			i++;
		}
	}*/
}

static int	witch_panel_clicked(t_vector2d loc, t_info *info)
{
	int	updateviewport;

	updateviewport = FAILED;
	if (aabb(info->screen.viewmode_area, loc) == GOOD)
		updateviewport = witch_viewmode_button_clicked(loc, info);
	else if (aabb(info->screen.viewport_area, loc) == GOOD)
		updateviewport = viewport_clicked(loc, info);
	return (updateviewport);
}

void		mouse_input(t_bool *quit, t_info *info, SDL_Event *event)
{
	int			updateviewport;
	t_vector2d	mouse_location;

	mouse_location.x = event->motion.x;
	mouse_location.y = event->motion.y;
	updateviewport = FAILED;
	if (event->button.button == SDL_BUTTON_LEFT)
		updateviewport = witch_panel_clicked(mouse_location, info);
	if (updateviewport == GOOD)
	{
		info->screen.resolution = FIRST_RESOLUTION;
		draw_calls_add(info, DRAWCALL_VIEWPORT);
	}
}
