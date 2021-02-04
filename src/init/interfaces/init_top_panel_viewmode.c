/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_top_panel_viewmode.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 14:53:32 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 14:46:29 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_viewmode_scrollbar_button(t_viewmode_scrollbox *viewmode)
{
	viewmode->scrollbar.button.area = viewmode->scrollbar.area;
	viewmode->scrollbar.button.area.x = viewmode->current;
	viewmode->scrollbar.button.hover_color = BUTTON_HOVER_COLOR;
	viewmode->scrollbar.button.color = BUTTON_COLOR;
	viewmode->scrollbar.button.ishover = 0;
	viewmode->scrollbar.button.clicked = NULL;
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

static void	init_viewmode_scrollbar(t_viewmode_scrollbox *viewmode)
{
	viewmode->scrollbar.max =
		viewmode->viewmode_list[VIEWMODE_BUTTON_AMOUNT - 1].area.x
		+ viewmode->viewmode_list[VIEWMODE_BUTTON_AMOUNT - 1].area.w;
	viewmode->scrollbar.area.x = 0;
	viewmode->scrollbar.area.y = TOP_PANEL_SIZE - SCROLLBAR_SIZE;
	viewmode->scrollbar.area.w = viewmode->area.w;
	viewmode->scrollbar.area.h = SCROLLBAR_SIZE;
	viewmode->scrollbar.color = SCROLLBAR_COLOR;
	viewmode->scrollbar.ratio = (viewmode->scrollbar.area.w
		/ (float)viewmode->scrollbar.max);
	init_viewmode_scrollbar_button(viewmode);
}

static void	set_clicked_action(t_viewmode_scrollbox *viewmode)
{
	viewmode->viewmode_list[0].clicked = game_viewmode_button_clicked;
	viewmode->viewmode_list[1].clicked = editor_viewmode_button_clicked;
	viewmode->viewmode_list[2].clicked = unlit_viewmode_button_clicked;
	viewmode->viewmode_list[3].clicked = iteration_viewmode_button_clicked;
	viewmode->viewmode_list[4].clicked = normal_viewmode_button_clicked;
	viewmode->viewmode_list[5].clicked =
		direct_illumination_viewmode_button_clicked;
	viewmode->viewmode_list[8].clicked = distance_fog_viewmode_button_clicked;
	viewmode->viewmode_list[6].clicked = NULL;
	viewmode->viewmode_list[7].clicked = NULL;
}

static void	init_viewmode_list(t_viewmode_scrollbox *viewmode)
{
	unsigned int	i;

	i = 0;
	while (i < VIEWMODE_BUTTON_AMOUNT)
	{
		viewmode->viewmode_list[i].area.h = (TOP_PANEL_SIZE - SCROLLBAR_SIZE)
			- TOP_PANEL_BUTTONS_MARGIN * 2;
		viewmode->viewmode_list[i].area.w = viewmode->viewmode_list[i].area.h;
		viewmode->viewmode_list[i].area.y = TOP_PANEL_BUTTONS_MARGIN;
		viewmode->viewmode_list[i].area.x = i * (TOP_PANEL_BUTTONS_MARGIN
			+ viewmode->viewmode_list[i].area.w);
		viewmode->viewmode_list[i].color = BUTTON_COLOR;
		viewmode->viewmode_list[i].hover_color = BUTTON_HOVER_COLOR;
		viewmode->viewmode_list[i].ishover = 0;
		i++;
	}
	set_clicked_action(viewmode);
}

int			init_viewmode_scrollbox(t_top_panel *panel)
{
	if ((panel->viewmode.viewmode_list = (t_button*)malloc(
		sizeof(t_button) * (VIEWMODE_BUTTON_AMOUNT + 1))) == NULL)
		return (MALLOC_ERROR);
	panel->viewmode.area.x = TOP_PANEL_BUTTONS_MARGIN * 2 +
		panel->savemap_button.area.x + panel->savemap_button.area.w;
	panel->viewmode.area.y = 0;
	panel->viewmode.area.w = WIN_WIDTH - panel->viewmode.area.x
		- panel->savemap_button.area.w - TOP_PANEL_BUTTONS_MARGIN * 3;
	panel->viewmode.area.h = TOP_PANEL_SIZE;
	panel->viewmode.current = 0;
	init_viewmode_list(&panel->viewmode);
	init_viewmode_scrollbar(&panel->viewmode);
	return (GOOD);
}
