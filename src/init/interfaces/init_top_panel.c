/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_top_panel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:49:23 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/03 14:17:18 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_save_button(t_top_panel *panel)
{
	panel->savemap_button.area.x = TOP_PANEL_BUTTONS_MARGIN;
	panel->savemap_button.area.y = TOP_PANEL_BUTTONS_MARGIN;
	panel->savemap_button.area.h =
		TOP_PANEL_SIZE - TOP_PANEL_BUTTONS_MARGIN * 2;
	panel->savemap_button.area.w = panel->savemap_button.area.h;
	panel->savemap_button.color = BUTTON_COLOR;
	panel->savemap_button.hover_color = BUTTON_HOVER_COLOR;
	panel->savemap_button.ishover = 0;
	panel->savemap_button.clicked = NULL;
}

static void	init_gpu_switch(t_top_panel *panel, int ongpu)
{
	panel->gpu_switch.area.x = panel->viewmode.area.w + panel->viewmode.area.x
		+ TOP_PANEL_BUTTONS_MARGIN * 2;
	panel->gpu_switch.area.y = TOP_PANEL_BUTTONS_MARGIN;
	panel->gpu_switch.area.h = panel->savemap_button.area.h;
	panel->gpu_switch.area.w = panel->savemap_button.area.w;
	panel->gpu_switch.color_on = BUTTON_SWITCH_COLOR_ON;
	panel->gpu_switch.color_off = BUTTON_SWITCH_COLOR_OFF;
	panel->gpu_switch.hover_color = BUTTON_HOVER_COLOR;
	panel->gpu_switch.ison = (ongpu == 1 ? 1 : 0);
	panel->gpu_switch.ishover = 0;
	panel->gpu_switch.clicked = gpu_switch_clicked;
}

int			init_top_panel(SDL_Renderer *renderer, t_top_panel *panel,
				int ongpu)
{
	int	code;

	panel->area.x = 0;
	panel->area.y = 0;
	panel->area.w = WIN_WIDTH;
	panel->area.h = TOP_PANEL_SIZE;
	init_save_button(panel);
	if ((code = init_viewmode_scrollbox(panel)) != GOOD)
		return (code);
	init_gpu_switch(panel, ongpu);
	if ((code = init_top_panel_images(renderer, panel)) != GOOD)
		return (code);
	return (GOOD);
}
