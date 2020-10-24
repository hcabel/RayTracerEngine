/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewmode.area.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:52:58 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 18:15:52 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	get_pixel_color_from_pixel_index(unsigned int i,
	unsigned int width, t_buttons_scrollbox *scrollbox)
{
	unsigned int	button_index;
	t_vector2d		coordinates;

	coordinates = get_pixel_coordinates(i, width);
	button_index = scrollbox->current;
	while (button_index < scrollbox->amount)
	{
		if (aabb(scrollbox->list[button_index].area, coordinates) == GOOD)
			return (scrollbox->list[button_index].ishover.bool == 1 ?
				scrollbox->list[button_index].hover_color :
				scrollbox->list[button_index].color);
		button_index++;
	}
	if (aabb(scrollbox->scrollbar_area, coordinates) == GOOD)
	{
		if (aabb(scrollbox->scrollbar_button.area, coordinates) == GOOD)
			return (scrollbox->scrollbar_button.ishover.bool ?
				scrollbox->scrollbar_button.hover_color :
				scrollbox->scrollbar_button.color);
		return (scrollbox->scrollbar_color);
	}
	return (VIEWMODE_BACKGROUND_COLOR);
}

void		new_viewmode_panel_frame(t_info *info)
{
	unsigned int	color;
	unsigned int	i;

	ft_printf("[DrawCall] ViewMode panel\n");
	SDL_LockTexture(info->screen.tex, &info->screen.viewmode.area,
		&info->screen.viewmode.pixels, &info->screen.pitch);
	i = 0;
	while (i < info->screen.viewmode.area.w * info->screen.viewmode.area.h)
	{
		color = get_pixel_color_from_pixel_index(i,
			info->screen.viewmode.area.w, &info->screen.viewmode.scrollbox);
		((unsigned int*)info->screen.viewmode.pixels)[i % info->screen.viewmode.area.w
			+ (i / info->screen.viewmode.area.w * WIN_WIDTH)] = color;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex,
		&info->screen.viewmode.area, &info->screen.viewmode.area);
	display_viewmode_images(info->renderer, &info->screen.viewmode);
	SDL_RenderPresent(info->renderer);
}
