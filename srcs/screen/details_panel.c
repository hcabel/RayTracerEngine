/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:52:54 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 17:37:53 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static unsigned int	get_selector_color(t_vector2d loc, t_selector *selector)
{
	loc.x -= selector->area.x;
	loc.y -= selector->area.y;
	if (aabb(selector->b_left.area, loc) == GOOD)
		return (selector->b_left.ishover == 1 ? selector->b_left.color :
			selector->b_left.hover_color);
	else if (aabb(selector->b_right.area, loc) == GOOD)
		return (selector->b_right.ishover == 1 ? selector->b_right.color :
			selector->b_right.hover_color);
	else if (aabb(selector->preview_area, loc) == GOOD)
		return (0);
	return (0);
}

unsigned int		get_pixel_color(t_vector2d loc, t_details_panel *details)
{
	if (aabb(details->shape_selector.area, loc) == GOOD)
		return (get_selector_color(loc, &details->shape_selector));
	if (aabb(details->addcomponent.area, loc) == GOOD)
		return (details->addcomponent.color);
	return (0x444444FF);
}

void				new_details_panel_frame(t_info *info)
{
	unsigned int	color;
	int				i;

	ft_printf("[DrawCall] Details panel\n");
	SDL_LockTexture(info->screen.tex, &info->screen.details.area,
		&info->screen.pixels, &info->screen.pitch);
	i = 0;
	while (i < info->screen.details.area.w *
		info->screen.details.area.h)
	{
		color = get_pixel_color(get_pixel_coordinates(i,
			info->screen.details.area.w), &info->screen.details);
		((unsigned int*)info->screen.pixels)[i % info->screen.details.area.w +
			(i / info->screen.details.area.w * WIN_WIDTH)] = color;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex, NULL, NULL);
	SDL_RenderPresent(info->renderer);
}
