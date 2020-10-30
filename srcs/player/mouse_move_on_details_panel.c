/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_on_details_panel.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:04:37 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/30 09:53:14 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	move_on_selector(t_vector2d loc, t_selector *selector)
{
	int	result;

	loc.x -= selector->area.x;
	loc.y -= selector->area.y;
	result = FAILED;
	if (aabb(selector->b_left.area, loc) == GOOD)
	{
		if (selector->b_left.ishover.bool != 1)
			result = GOOD;
		selector->b_left.ishover.bool = 1;
	}
	else if (selector->b_left.ishover.bool == 1)
	{
		selector->b_left.ishover.bool = 0;
		result = GOOD;
	}
	if (aabb(selector->b_right.area, loc) == GOOD)
	{
		if (selector->b_right.ishover.bool != 1)
			result = GOOD;
		selector->b_right.ishover.bool = 1;
	}
	else if (selector->b_right.ishover.bool == 1)
	{
		selector->b_right.ishover.bool = 0;
		result = GOOD;
	}
	return (result);
}

static int	move_on_triple_switch_axis(t_vector2d loc, t_triple_switch *axis)
{
	int	result;

	loc.x -= axis->area.x;
	loc.y -= axis->area.y;
	result = FAILED;
	if (aabb(axis->first.area, loc) == GOOD)
	{
		if (axis->first.ishover.bool != 1)
			result = GOOD;
		axis->first.ishover.bool = 1;
	}
	else if (axis->first.ishover.bool == 1)
	{
		axis->first.ishover.bool = 0;
		result = GOOD;
	}
	if (aabb(axis->second.area, loc) == GOOD)
	{
		if (axis->second.ishover.bool != 1)
			result = GOOD;
		axis->second.ishover.bool = 1;
	}
	else if (axis->second.ishover.bool == 1)
	{
		axis->second.ishover.bool = 0;
		result = GOOD;
	}
	if (aabb(axis->third.area, loc) == GOOD)
	{
		if (axis->third.ishover.bool != 1)
			result = GOOD;
		axis->third.ishover.bool = 1;
	}
	else if (axis->third.ishover.bool == 1)
	{
		axis->third.ishover.bool = 0;
		result = GOOD;
	}
	return (result);
}

int			move_on_details_panel(t_vector2d loc, t_details_panel *panel)
{
	loc.x -= panel->area.x;
	loc.y -= panel->area.y;
	if (move_on_selector(loc, &panel->shape_selector) == GOOD)
		return (GOOD);
	if (move_on_triple_switch_axis(loc, &panel->triple_switch_axis) == GOOD)
		return (GOOD);
	return (FAILED);
}
