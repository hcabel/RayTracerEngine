/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:11:59 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/04 14:42:34 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	resize_viewport_panel(t_vector2d window_size,
				t_viewport_panel *panel, SDL_Renderer *renderer)
{
	SDL_DestroyTexture(panel->tex);
	panel->tex = NULL;
	if (renderer != NULL)
		panel->tex = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
			window_size.x, window_size.y);
	if (!panel->tex)
		return (SDL_TEXTURE_CREATION_ERROR);
	panel->area.w = window_size.x - LEFT_PANEL_SIZE;
	panel->area.h = window_size.y - TOP_PANEL_SIZE;
	return (GOOD);
}

static void	resize_left_panel(t_vector2d window_size, t_left_panel *panel)
{
	panel->area.h = window_size.y - TOP_PANEL_SIZE;
}

static int	confirm_window_size(t_vector2d window_size, t_info *info)
{
	if (window_size.x <= LEFT_PANEL_SIZE && window_size.y <= TOP_PANEL_SIZE)
		SDL_SetWindowSize(info->window, LEFT_PANEL_SIZE, TOP_PANEL_SIZE);
	else if (window_size.x <= LEFT_PANEL_SIZE)
		SDL_SetWindowSize(info->window, LEFT_PANEL_SIZE, window_size.y);
	else if (window_size.x <= LEFT_PANEL_SIZE)
		SDL_SetWindowSize(info->window, window_size.x, TOP_PANEL_SIZE);
	if (window_size.x <= LEFT_PANEL_SIZE || window_size.y <= TOP_PANEL_SIZE)
		return (RESIZE_WINDOW_ERROR);
	return (GOOD);
}

int			resize_window(t_info *info)
{
	t_vector2d	window_size;
	int			x;
	int			y;

	if (!ABLE_TO_RESIZE)
		return (RESIZE_NOT_ALLOW);
	SDL_GetWindowSize(info->window, &x, &y);
	window_size.x = x;
	window_size.y = y;
	if (confirm_window_size(window_size, info) != GOOD)
		return (RESIZE_WINDOW_ERROR);
	resize_top_panel(window_size, &info->screen.top);
	resize_left_panel(window_size, &info->screen.left);
	SDL_DestroyTexture(info->screen.tex);
	if (!(info->screen.tex = SDL_CreateTexture(info->renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		window_size.x, window_size.y)))
		return (SDL_TEXTURE_CREATION_ERROR);
	info->screen.area.w = window_size.x;
	info->screen.area.h = window_size.y;
	resize_viewport_panel(window_size, &info->screen.viewport,
		info->renderer);
	info->screen.viewport.resolution = FIRST_RESOLUTION;
	set_multiple_drawcall_from_code(0x7, info);
	return (GOOD);
}
