/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_on_top_panel.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:19:15 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 13:27:41 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		press_on_top_panel(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.top.viewmode.area.x;
	loc.y -= info->screen.top.viewmode.area.y;
	i = 0;
	while (i < VIEWMODE_BUTTON_AMOUNT)
	{
		if (aabb(info->screen.top.viewmode.viewmode_list[i].area, loc) == GOOD)
		{
			ft_printf("clicked on %d\n", i);
			if (info->screen.top.viewmode.viewmode_list[i].clicked(info) == GOOD)
				return (1);
		}
		i++;
	}
	return (0);
}
