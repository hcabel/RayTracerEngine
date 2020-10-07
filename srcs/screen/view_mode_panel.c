/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewmode_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:52:58 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/06 18:15:52 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	get_pixel_color_from_pixel_index(unsigned int i,
	unsigned int width, t_scrollbox *scrollbox)
{
	unsigned int	button_index;
	t_vector2d		coordinates;

	coordinates = get_pixel_coordinates(i, width);
	button_index = scrollbox->current;
	while (button_index < scrollbox->amount)
	{
		if (aabb(scrollbox->list[button_index].area, coordinates) == GOOD)
			return (scrollbox->list[button_index].color);
		button_index++;
	}
	if (aabb(scrollbox->scrollbar_area, coordinates) == GOOD)
	{
		if (aabb(scrollbox->scrollbar_button.area, coordinates) == GOOD)
			return (scrollbox->scrollbar_button.color);
		return (scrollbox->scrollbar_color);
	}
	return (scrollbox->color);
}

void		new_viewmode_panel_frame(t_info *info)
{
	unsigned int	color;
	unsigned int	i;

	ft_printf("[DrawCall] ViewMode panel\n");
	SDL_LockTexture(info->screen.tex, &info->screen.viewmode_panel,
		&info->screen.pixels, &info->screen.pitch);
	i = 0;
	while (i < info->screen.viewmode_panel.w * info->screen.viewmode_panel.h)
	{
		color = get_pixel_color_from_pixel_index(i,
			info->screen.viewmode_panel.w, &info->screen.viewmode_content);
		((unsigned int*)info->screen.pixels)[i % info->screen.viewmode_panel.w
			+ (i / info->screen.viewmode_panel.w * WIN_WIDTH)] = color;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex, NULL, NULL);
	SDL_RenderPresent(info->renderer);
}
