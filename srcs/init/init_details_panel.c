/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_details_panel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:12:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/03 14:44:04 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_selector(t_selector *selector)
{
	selector->preview_area.w = DETAILS_AREA_SIZE / 3;
	selector->preview_area.h = selector->preview_area.w;
	selector->preview_area.x = 20;
	selector->preview_area.y = 0;
	selector->area.w = selector->preview_area.w + 20 * 2;
	selector->area.h = selector->preview_area.h;
	selector->area.x = (DETAILS_AREA_SIZE - selector->area.w) / 2;
	selector->area.y = DETAILS_BUTTONS_MARGIN;
	selector->b_left.area.w = 20;
	selector->b_left.area.h = selector->preview_area.h;
	selector->b_left.area.x = 0;
	selector->b_left.area.y = 0;
	selector->b_left.color = BUTTON_COLOR;
	selector->b_left.hover_color = BUTTON_HOVER_COLOR;
	selector->b_left.ishover.bool = 0;
	selector->b_left.clicked = decrease_target_shape;
	selector->b_right.area.w = 20;
	selector->b_right.area.h = selector->preview_area.h;
	selector->b_right.area.x = selector->area.w - 20;
	selector->b_right.area.y = 0;
	selector->b_right.color = BUTTON_COLOR;
	selector->b_right.hover_color = BUTTON_HOVER_COLOR;
	selector->b_right.ishover.bool = 0;
	selector->b_right.clicked = increase_target_shape;
	selector->preview = shape_selector_display;
}

static void	init_buttons(t_details_panel *details)
{
	details->addcomponent.area.x = 0;
	details->addcomponent.area.y = details->area.h - 20;
	details->addcomponent.area.w = details->area.w;
	details->addcomponent.area.h = 20;
	details->addcomponent.color = BUTTON_COLOR;
	details->addcomponent.hover_color = BUTTON_HOVER_COLOR;

}

static void	init_triple_switch_axis(t_triple_switch *axis,
				int previous_panel_y_bottom_coordinate)
{
	axis->area.x = DETAILS_AREA_SIZE / 20;
	axis->area.y = previous_panel_y_bottom_coordinate + DETAILS_BUTTONS_MARGIN;
	axis->area.w = DETAILS_AREA_SIZE - (DETAILS_AREA_SIZE / 20 * 2);
	axis->area.h = 30;
	axis->selected_button = 0;
	axis->selected_color = BUTTON_SELECTED_COLOR;
	axis->first.area.h = axis->area.h;
	axis->first.area.w = axis->area.w / 3;
	axis->first.area.x = 0;
	axis->first.area.y = 0;
	axis->first.color = BUTTON_COLOR;
	axis->first.hover_color = BUTTON_HOVER_COLOR;
	axis->first.ishover.bool = 0;
	axis->first.clicked = set_transphorm_axis_x;
	axis->second.area.h = axis->area.h;
	axis->second.area.w = axis->area.w / 3;
	axis->second.area.x = axis->first.area.w;
	axis->second.area.y = 0;
	axis->second.color = BUTTON_COLOR;
	axis->second.hover_color = BUTTON_HOVER_COLOR;
	axis->second.ishover.bool = 0;
	axis->second.clicked = set_transphorm_axis_y;
	axis->third.area.h = axis->area.h;
	axis->third.area.w = axis->area.w / 3;
	axis->third.area.x = axis->first.area.w + axis->second.area.w;
	axis->third.area.y = 0;
	axis->third.color = BUTTON_COLOR;
	axis->third.hover_color = BUTTON_HOVER_COLOR;
	axis->third.ishover.bool = 0;
	axis->third.clicked = set_transphorm_axis_z;
}

int			init_details_panel(t_details_panel *details)
{
	int	error_code;

	details->skip_selector_preview.bool = 0;
	details->area.x = 0;
	details->area.y = VIEWMODE_AREA_SIZE;
	details->area.w = DETAILS_AREA_SIZE;
	details->area.h = WIN_HEIGTH - details->area.y;
	init_selector(&details->shape_selector);
	init_triple_switch_axis(&details->triple_switch_axis,
		details->shape_selector.area.h + details->shape_selector.area.y);
	details->tri_vector_pannel.x = DETAILS_AREA_SIZE / 20;
	details->tri_vector_pannel.y = + details->triple_switch_axis.area.h
		+ details->triple_switch_axis.area.y + DETAILS_BUTTONS_MARGIN;
	details->tri_vector_pannel.w = DETAILS_AREA_SIZE
		- (DETAILS_AREA_SIZE / 20 * 2);
	details->tri_vector_pannel.h = 60;
	init_buttons(details);
	return (GOOD);
}
