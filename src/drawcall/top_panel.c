/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   top_panel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 17:09:34 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 19:08:47 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	get_pixel_color_from_pixel_location_in_viewmode(t_top_panel *panel,
				t_vector2d coord)
{
	unsigned int	i;
	float			ratio;

	coord.x -= panel->viewmode.area.x;
	coord.y -= panel->viewmode.area.y;
	if (panel->viewmode.scrollbar.enable)
	if (aabb(panel->viewmode.scrollbar.area, coord) == GOOD)
	{
		if (!panel->viewmode.scrollbar.enable)
			return (TOP_PANEL_BACKGROUND_COLOR);
		if (aabb(panel->viewmode.scrollbar.button.area, coord) == GOOD)
			return (panel->viewmode.scrollbar.button.ishover ?
				panel->viewmode.scrollbar.button.hover_color :
				panel->viewmode.scrollbar.button.color);
		return (SCROLLBAR_COLOR);
	}
	coord.x += panel->viewmode.current;
	i = 0;
	while (i < VIEWMODE_BUTTON_AMOUNT)
	{
		if (aabb(panel->viewmode.viewmode_list[i].area, coord) == GOOD)
			return (panel->viewmode.viewmode_list[i].ishover ?
				panel->viewmode.viewmode_list[i].hover_color :
				panel->viewmode.viewmode_list[i].color);
		i++;
	}
	return (TOP_PANEL_BACKGROUND_COLOR);
}

static int	get_pixel_color_from_pixel_location(t_vector2d coord,
				t_top_panel *panel)
{
	if (aabb(panel->savemap_button.area, coord) == GOOD)
		return (panel->savemap_button.ishover ?
			panel->savemap_button.hover_color : panel->savemap_button.color);
	if (aabb(panel->viewmode.area, coord) == GOOD)
		return (get_pixel_color_from_pixel_location_in_viewmode(panel, coord));
	return (TOP_PANEL_BACKGROUND_COLOR);
}

int			drawcall_top_panel(t_info *info)
{
	unsigned int	color;
	unsigned int	i;
	t_vector2d		coord;

	ft_printf("[DrawCall] Top panel\n");
	SDL_LockTexture(info->screen.tex, &info->screen.top.area,
		&info->screen.top.pixels, &info->screen.pitch);

	i = 0;
	while (i < info->screen.top.area.w * info->screen.top.area.h)
	{
		coord = get_pixel_coordinates(i, info->screen.top.area.w);
		color = get_pixel_color_from_pixel_location(coord, &info->screen.top);
		((unsigned int*)info->screen.top.pixels)[(int)coord.y
			* info->screen.top.area.w + (int)coord.x] = color;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex,
		&info->screen.top.area, &info->screen.top.area);
	//display_viewmode_images(info->renderer, &info->screen.top);
	SDL_RenderPresent(info->renderer);
	return (GOOD);
}