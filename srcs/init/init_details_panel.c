/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_details_panel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:12:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 17:45:42 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_selector(t_selector *selector)
{
	selector->preview_area.w = DETAILS_AREA_SIZE / 3;
	selector->preview_area.h = selector->preview_area.w;
	selector->preview_area.x = (DETAILS_AREA_SIZE - selector->preview_area.w)
		/ 3;
	selector->preview_area.y = DETAILS_BUTTONS_MARGIN;
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
	selector->b_left.ishover = 0;
	selector->b_left.clicked = NULL; // todo
	selector->b_right.area.w = 20;
	selector->b_right.area.h = selector->preview_area.h;
	selector->b_right.area.x = selector->area.w - 20;
	selector->b_right.area.y = 0;
	selector->b_right.color = BUTTON_COLOR;
	selector->b_right.hover_color = BUTTON_HOVER_COLOR;
	selector->b_right.ishover = 0;
	selector->b_right.clicked = NULL; // todo
	// draw preview function
}

static void	init_buttons(t_details_panel *details)
{
	details->addcomponent.area.x = 0;
	details->addcomponent.area.y = details->area.h - 20;
	details->addcomponent.area.w = details->area.w;
	details->addcomponent.area.h = 20;
	details->addcomponent.color = BUTTON_COLOR;

}

int			init_details_panel(t_details_panel *details)
{
	int	error_code;

	details->area.x = 0;
	details->area.y = VIEWMODE_AREA_SIZE;
	details->area.w = DETAILS_AREA_SIZE;
	details->area.h = WIN_HEIGTH - details->area.y;
	init_selector(&details->shape_selector);
	init_buttons(details);
	/*if ((error_code = malloc_scrollbox(details,
		DETAILS_SCROLLBOX_BUTTON_AMOUNT)) != GOOD)
		return (error_code);
	details->amount = DETAILS_SCROLLBOX_BUTTON_AMOUNT;
	details->area.h = WIN_HEIGTH;
	details->area.w = DETAILS_AREA_SIZE;
	details->area.x = 0;
	details->area.y = 0;
	details->color = DETAILS_BACKGROUND_COLOR;
	details->scrollbar_area.x = DETAILS_AREA_SIZE - SCROLLBAR_SIZE;
	details->scrollbar_area.y = 0;
	details->scrollbar_area.h = WIN_HEIGTH;
	details->scrollbar_area.w = SCROLLBAR_SIZE;
	details->scrollbar_color = DETAILS_SCROLLBAR_COLOR;
	init_scrollbar(details);;*/
	return (GOOD);
}
