/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_on_top_panel.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:16:27 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 17:15:13 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	button_status_update(t_button *button, t_vector2d loc)
{
	if (aabb(button->area, loc) == GOOD)
	{
		if (button->ishover == 1)
			return (FAILED);
		button->ishover = 1;
		return (GOOD);
	}
	if (button->ishover == 0)
		return (FAILED);
	button->ishover = 0;
	return (GOOD);
}

static int	move_on_viewmode_scrollbox(t_top_panel *panel,
				t_vector2d cursorlocation)
{
	int				result;
	unsigned int	i;

	cursorlocation.x -= panel->viewmode.area.x - panel->viewmode.current;
	cursorlocation.y -= panel->viewmode.area.y;
	result = 0;
	i = 0;
	while (i < VIEWMODE_BUTTON_AMOUNT)
	{
		if (button_status_update(&panel->viewmode.viewmode_list[i],
			cursorlocation) == GOOD)
			result |= 2;
		i++;
	}
	return (result);
}

int			move_on_top_panel(t_top_panel *panel, t_vector2d cursorlocation)
{
	int	result;

	result = 0;
	cursorlocation.x -= panel->area.x;
	cursorlocation.y -= panel->area.y;
	if (button_status_update(&panel->savemap_button, cursorlocation) == GOOD)
		result |= 2;
	result |= move_on_viewmode_scrollbox(panel, cursorlocation);
	return (result);
}
