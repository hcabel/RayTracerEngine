/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_on_viewmode_panel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:16:27 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/29 13:16:53 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		move_on_viewmode_panel(t_vector2d loc, t_viewmode_panel *viewmode)
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
