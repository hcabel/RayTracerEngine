/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:11:59 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/24 13:52:18 by hcabel           ###   ########.fr       */
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
	panel->viewmode.area.w = window_size.x - panel->viewmode.area.x
		- TOP_PANEL_BUTTONS_MARGIN * 2 - panel->gpu_switch.area.w;
	panel->viewmode.scrollbar.area.w = panel->viewmode.area.w;
	panel->viewmode.scrollbar.ratio =
		(panel->viewmode.scrollbar.area.w / (float)panel->viewmode.scrollbar.max);

	max = (panel->viewmode.scrollbar.max) - panel->viewmode.area.w;
	if (panel->viewmode.current > max)
		panel->viewmode.current = max;

	init_viewmode_scrollbar_button(&panel->viewmode);

	panel->gpu_switch.area.x = panel->viewmode.area.w + panel->viewmode.area.x
		+ TOP_PANEL_BUTTONS_MARGIN;
}

static int	resize_viewport_panel(t_vector2d window_size, SDL_Event *event,
				t_viewport_panel *panel, SDL_Renderer *renderer)
{
	SDL_DestroyTexture(panel->tex);

	if (!(panel->tex = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		window_size.x, window_size.y)))
		return (SDL_TEXTURE_CREATION_ERROR);
	panel->area.w = window_size.x - LEFT_PANEL_SIZE;
	panel->area.h = window_size.y - TOP_PANEL_SIZE;
}

static void	resize_left_panel(t_vector2d window_size, t_left_panel *panel,
				SDL_Event *event)
{
	unsigned int	max;

	panel->area.h = window_size.y - TOP_PANEL_SIZE;
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
	resize_left_panel(window_size, &info->screen.left, event);
	SDL_DestroyTexture(info->screen.tex);
	if (!(info->screen.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		window_size.x, window_size.y)))
		return (SDL_TEXTURE_CREATION_ERROR);
	info->screen.area.w = window_size.x;
	info->screen.area.h = window_size.y;

	resize_viewport_panel(window_size, event, &info->screen.viewport,
		info->renderer);

	info->screen.viewport.resolution = FIRST_RESOLUTION;
	drawcall_add(info, DRAWCALL_VIEWPORT);
	drawcall_add(info, DRAWCALL_TOP_PANEL);
	drawcall_add(info, DRAWCALL_LEFT_PANEL);
	return (GOOD);
}