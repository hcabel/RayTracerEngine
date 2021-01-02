/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_on_top_panel.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:19:15 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/02 13:47:22 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		clicked_on_viewmode(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.top.viewmode.area.x;
	loc.y -= info->screen.top.viewmode.area.y;
	i = 0;
	while (i < VIEWMODE_BUTTON_AMOUNT)
	{
		if (aabb(info->screen.top.viewmode.viewmode_list[i].area, loc) == GOOD)
		{
			if (info->screen.top.viewmode.viewmode_list[i].clicked == NULL)
				return (BUTTON_FUNCTION_NOT_SET);
			if (info->screen.top.viewmode.viewmode_list[i].clicked(info) == GOOD)
				return (1);
		}
		i++;
	}
	return (0);
}

int		press_on_top_panel(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	if (aabb(info->screen.top.gpu_switch.area, loc) == GOOD)
	{
		return (info->screen.top.gpu_switch.clicked(info,
			&info->screen.top.gpu_switch));
	}
	else if (aabb(info->screen.top.viewmode.area, loc) == GOOD)
		return (clicked_on_viewmode(loc, info));
	return (0);
}
