/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 11:23:36 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		viewport_clicked(t_vector2d loc, t_info *info)
{
	loc.x -= 0;
	loc.y -= 0;
	if (!info)
		return (0);
	return (0);
}

int		mouse_press(t_info *info)
{
	int	result;
	int	tmp;

	result = 0;
	if (aabb(info->screen.top.area, info->mouse.location) == GOOD)
	{
		if ((tmp = press_on_top_panel(info->mouse.location, info)) < 0)
			return (tmp);
		result |= tmp;
	}
	else if (aabb(info->screen.viewport.area, info->mouse.location) == GOOD)
		result |= viewport_clicked(info->mouse.location, info);
	else if (aabb(info->screen.left.area, info->mouse.location) == GOOD)
		result |= press_on_left_panel(info->mouse.location, info);
	set_multiple_drawcall_from_code(result, info);
	return (GOOD);
}
