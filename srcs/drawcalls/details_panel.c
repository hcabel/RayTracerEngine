/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:52:54 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/24 13:48:39 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static unsigned int	get_selector_color(t_vector2d loc, t_selector *selector,
						t_info *info)
{
	loc.x -= selector->area.x;
	loc.y -= selector->area.y;
	if (aabb(selector->preview_area, loc) == GOOD)
		return (selector->preview(loc, info));
	else if (aabb(selector->b_left.area, loc) == GOOD)
		return (selector->b_left.ishover.bool == 1 ?
			selector->b_left.hover_color : selector->b_left.color);
	else if (aabb(selector->b_right.area, loc) == GOOD)
		return (selector->b_right.ishover .bool== 1 ?
			selector->b_right.hover_color : selector->b_right.color);
	return (0);
}

unsigned int		get_pixel_color(t_vector2d loc, t_details_panel *details,
						t_info *info)
{
	if (aabb(details->shape_selector.area, loc) == GOOD)
		return (get_selector_color(loc, &details->shape_selector, info));
	if (aabb(details->addcomponent.area, loc) == GOOD)
		return (details->addcomponent.ishover.bool == 1 ?
			details->addcomponent.hover_color : details->addcomponent.color);
	return (DETAILS_BACKGROUND_COLOR);
}

void				new_details_panel_frame(t_info *info)
{
	unsigned int	color;
	int				i;

	ft_printf("[DrawCall] Details panel\n");
	SDL_LockTexture(info->screen.tex, &info->screen.details.area,
		&info->screen.details.pixels, &info->screen.pitch);
	i = 0;
	while (i < info->screen.details.area.w *
		info->screen.details.area.h)
	{
		color = get_pixel_color(get_pixel_coordinates(i,
			info->screen.details.area.w), &info->screen.details, info);
		((unsigned int*)info->screen.details.pixels)[i % info->screen.details.area.w +
			(i / info->screen.details.area.w * WIN_WIDTH)] = color;
		i++;
	}
	SDL_UnlockTexture(info->screen.tex);
	SDL_RenderCopy(info->renderer, info->screen.tex,
		&info->screen.details.area, &info->screen.details.area);
	SDL_RenderPresent(info->renderer);
}
