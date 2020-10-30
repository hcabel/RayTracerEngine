/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_on_details_panel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:19:23 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/29 13:25:52 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		press_on_details_panel(t_vector2d loc, t_info *info)
{
	loc.x -= info->screen.details.area.x;
	loc.y -= info->screen.details.area.y;
	loc.x -= info->screen.details.shape_selector.area.x;
	loc.y -= info->screen.details.shape_selector.area.y;
	if (aabb(info->screen.details.shape_selector.b_left.area, loc) == GOOD)
		return (info->screen.details.shape_selector.b_left.clicked(info));
	if (aabb(info->screen.details.shape_selector.b_right.area, loc) == GOOD)
		return (info->screen.details.shape_selector.b_right.clicked(info));
	return (FAILED);
}
