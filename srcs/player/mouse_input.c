/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/08 17:03:19 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	witch_viewmode_button_clicked(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.viewmode_area.x;
	loc.y -= info->screen.viewmode_area.y;
	i = 0;
	while (i < info->screen.viewmode_content.amount)
	{
		if (aabb(info->screen.viewmode_content.list[i].area, loc) == GOOD)
		{
			info->screen.viewmode_content.list[i].clicked(info);
			break ;
		}
		else
			i++;
	}
}

static void	viewport_clicked(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.viewmode_area.x;
	loc.y -= info->screen.viewmode_area.y;
	i = 0;
	while (i < info->screen.viewmode_content.amount)
	{
		if (aabb(info->screen.viewmode_content.list[i].area, loc) == GOOD)
		{
			info->screen.viewmode_content.list[i].clicked(info);
			printf("GOOD\n");
			break ;
		}
		else
		{
			i++;
		}
	}
}

static void	witch_panel_clicked(t_vector2d loc, t_info *info)
{
	if (aabb(info->screen.viewmode_area, loc) == GOOD)
		witch_viewmode_button_clicked(loc, info);
	else if (aabb(info->screen.viewport_area, loc) == GOOD)
		viewport_clicked(loc, info);
}

void		mouse_input(t_bool *quit, t_info *info, SDL_Event *event)
{
	t_vector2d	mouse_location;

	mouse_location.x = event->motion.x;
	mouse_location.y = event->motion.y;
	if (event->button.button == SDL_BUTTON_LEFT)
		witch_panel_clicked(mouse_location, info);
	info->screen.resolution = FIRST_RESOLUTION;
	draw_calls_add(info, DRAWCALL_VIEWPORT);
}
