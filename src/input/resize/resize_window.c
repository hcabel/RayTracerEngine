/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:11:59 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/29 12:23:12 by hcabel           ###   ########.fr       */
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


static void	resize_top_panel(t_vector2d window_size, t_top_panel *panel,
				SDL_Event *event)
{
	unsigned int	max;

	panel->area.w = window_size.x;
	panel->viewmode.area.w = window_size.x - panel->viewmode.area.x;
	panel->viewmode.scrollbar.area.w = panel->viewmode.area.w;
	panel->viewmode.scrollbar.ratio =
		(panel->viewmode.scrollbar.area.w / (float)panel->viewmode.scrollbar.max);

	max = (panel->viewmode.scrollbar.max) - panel->viewmode.area.w;
	if (panel->viewmode.current > max)
		panel->viewmode.current = max;

	init_viewmode_scrollbar_button(&panel->viewmode);
}

int			resize_window(int *quit, t_info *info, SDL_Event *event)
{
	t_vector2d	window_size;
	int			x;
	int			y;

	ft_printf("[Event] Resize\n");

	SDL_GetWindowSize(info->window, &x, &y);
	window_size.x = x;
	window_size.y = y;

	if (window_size.x <= LEFT_PANEL_SIZE && window_size.y <= TOP_PANEL_SIZE)
		SDL_SetWindowSize(info->window, LEFT_PANEL_SIZE, TOP_PANEL_SIZE);
	else if (window_size.x <= LEFT_PANEL_SIZE)
		SDL_SetWindowSize(info->window, LEFT_PANEL_SIZE, window_size.y);
	else if (window_size.x <= LEFT_PANEL_SIZE)
		SDL_SetWindowSize(info->window, window_size.x, TOP_PANEL_SIZE);

	if (window_size.x <= LEFT_PANEL_SIZE || window_size.y <= TOP_PANEL_SIZE)
		return (RESIZE_WINDOW_ERROR);


	resize_top_panel(window_size, &info->screen.top, event);

	info->screen.left.area.h = window_size.y - TOP_PANEL_SIZE;

	SDL_DestroyTexture(info->screen.tex);
	SDL_DestroyTexture(info->screen.viewport.tex);

	if (!(info->screen.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		window_size.x, window_size.y)))
		return (SDL_TEXTURE_CREATION_ERROR);
	if (!(info->screen.viewport.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		window_size.x, window_size.y)))
		return (SDL_TEXTURE_CREATION_ERROR);

	drawcall_add(info, DRAWCALL_VIEWPORT);
	drawcall_add(info, DRAWCALL_TOP_PANEL);
	drawcall_add(info, DRAWCALL_LEFT_PANEL);
	return (GOOD);
}