/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_on_details_panel.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:19:23 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/03 10:55:00 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_on_shape_selector(t_vector2d loc, t_info *info)
{
	loc.x -= info->screen.details.shape_selector.area.x;
	loc.y -= info->screen.details.shape_selector.area.y;
	if (aabb(info->screen.details.shape_selector.b_left.area, loc) == GOOD)
		return (info->screen.details.shape_selector.b_left.clicked(info));
	if (aabb(info->screen.details.shape_selector.b_right.area, loc) == GOOD)
		return (info->screen.details.shape_selector.b_right.clicked(info));
}

static int	check_on_triple_switch_axis(t_vector2d loc, t_info *info)
{
	loc.x -= info->screen.details.triple_switch_axis.area.x;
	loc.y -= info->screen.details.triple_switch_axis.area.y;
	if (aabb(info->screen.details.triple_switch_axis.first.area, loc) == GOOD)
		return (info->screen.details.triple_switch_axis.first.clicked(info));
	if (aabb(info->screen.details.triple_switch_axis.second.area, loc) == GOOD)
		return (info->screen.details.triple_switch_axis.second.clicked(info));
	if (aabb(info->screen.details.triple_switch_axis.third.area, loc) == GOOD)
		return (info->screen.details.triple_switch_axis.third.clicked(info));
}

int		press_on_details_panel(t_vector2d loc, t_info *info)
{

	loc.x -= info->screen.details.area.x;
	loc.y -= info->screen.details.area.y;
	if (check_on_shape_selector(loc, info) == GOOD)
		return (GOOD);
	if (check_on_triple_switch_axis(loc, info) == GOOD)
		return (GOOD);
	return (FAILED);
}
