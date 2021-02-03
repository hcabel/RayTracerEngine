/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_top_panel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 13:49:11 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 13:34:17 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_viewmode_scrollbar_button(t_viewmode_scrollbox *viewmode)
{
	viewmode->scrollbar.button.area = viewmode->scrollbar.area;
	viewmode->scrollbar.button.area.x = viewmode->current;
	if (viewmode->scrollbar.ratio < 1)
	{
		viewmode->scrollbar.button.area.w = viewmode->scrollbar.ratio
			* (viewmode->scrollbar.max / VIEWMODE_BUTTON_AMOUNT)
			* (1 + viewmode->area.w
			/ (viewmode->scrollbar.area.y - TOP_PANEL_BUTTONS_MARGIN));
		viewmode->scrollbar.enable = 1;
	}
	else
	{
		viewmode->scrollbar.button.area.w = viewmode->scrollbar.area.w;
		viewmode->scrollbar.enable = 0;
	}
}

void		resize_top_panel(t_vector2d window_size, t_top_panel *panel,
				SDL_Event *event)
{
	unsigned int	max;

	panel->area.w = window_size.x;
	panel->viewmode.area.w = window_size.x - panel->viewmode.area.x
		- TOP_PANEL_BUTTONS_MARGIN * 2 - panel->gpu_switch.area.w;
	panel->viewmode.scrollbar.area.w = panel->viewmode.area.w;
	panel->viewmode.scrollbar.ratio =
		(panel->viewmode.scrollbar.area.w
		/ (float)panel->viewmode.scrollbar.max);
	max = (panel->viewmode.scrollbar.max) - panel->viewmode.area.w;
	if (panel->viewmode.current > max)
		panel->viewmode.current = max;
	init_viewmode_scrollbar_button(&panel->viewmode);
	panel->gpu_switch.area.x = panel->viewmode.area.w + panel->viewmode.area.x
		+ TOP_PANEL_BUTTONS_MARGIN;
}
