/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_on_viewmode_panel.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:19:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/29 13:25:55 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		press_on_viewmode_panel(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.viewmode.area.x;
	loc.y -= info->screen.viewmode.area.y;
	i = 0;
	while (i < info->screen.viewmode.scrollbox.amount)
	{
		if (aabb(info->screen.viewmode.scrollbox.list[i].area, loc) == GOOD)
			return (info->screen.viewmode.scrollbox.list[i].clicked(info));
		else
			i++;
	}
	return (FAILED);
}
