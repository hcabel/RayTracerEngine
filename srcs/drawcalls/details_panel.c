/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   details_panel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:52:54 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/30 10:20:45 by hcabel           ###   ########.fr       */
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

static unsigned int	get_triple_switch_axis_color(t_vector2d loc,
						t_triple_switch *axis)
{
	loc.x -= axis->area.x;
	loc.y -= axis->area.y;
	if (aabb(axis->first.area, loc) == GOOD)
		return (axis->first.ishover.bool ? axis->first.hover_color
			: axis->first.color);
	if (aabb(axis->second.area, loc) == GOOD)
		return (axis->second.ishover.bool ? axis->second.hover_color
			: axis->second.color);
	if (aabb(axis->third.area, loc) == GOOD)
		return (axis->third.ishover.bool ? axis->third.hover_color
			: axis->third.color);
	return (0);
}

unsigned int		get_pixel_color(t_vector2d loc, t_details_panel *details,
						t_info *info)
{
	if (aabb(details->shape_selector.area, loc) == GOOD)
		return (get_selector_color(loc, &details->shape_selector, info));
	if (aabb(details->tri_vector_pannel, loc) == GOOD)
		return (0x111111FF);
	if (aabb(details->addcomponent.area, loc) == GOOD)
		return (details->addcomponent.ishover.bool == 1 ?
			details->addcomponent.hover_color : details->addcomponent.color);
	if (aabb(details->triple_switch_axis.area, loc) == GOOD)
		return (get_triple_switch_axis_color(loc, &details->triple_switch_axis));
	return (DETAILS_BACKGROUND_COLOR);
}

static void			print_trivector_value(SDL_Renderer **renderer,
	t_screen *screen, t_object *obj)
{
	SDL_Rect	textarea;
	char		*str;

	textarea = screen->details.tri_vector_pannel;
	textarea.y += VIEWMODE_AREA_SIZE;
	textarea.h = textarea.h / 3;
	str = ft_strjoin(ft_itoa(obj->location.x), "|");
	str = ft_strjoin(str, ft_strjoin(ft_itoa(obj->location.y), "|"));
	str = ft_strjoin(str, ft_itoa(obj->location.z));
	put_str_on_screen(*renderer, screen->font, &textarea, str);

	textarea.y += textarea.h;
	str = ft_strjoin(ft_itoa(obj->scale.x), "|");
	str = ft_strjoin(str, ft_strjoin(ft_itoa(obj->scale.y), "|"));
	str = ft_strjoin(str, ft_itoa(obj->scale.z));
	put_str_on_screen(*renderer, screen->font, &textarea, str);

	textarea.y += textarea.h;
	str = ft_strjoin(ft_itoa(obj->rotation.x), "|");
	str = ft_strjoin(str, ft_itoa(obj->rotation.y));
	put_str_on_screen(*renderer, screen->font, &textarea, str);
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

	if (info->scene.target != NULL)
		print_trivector_value(&info->renderer, &info->screen, info->scene.target);

	SDL_Rect textarea = info->screen.details.triple_switch_axis.area;
	textarea.y += VIEWMODE_AREA_SIZE;
	put_str_on_screen(info->renderer, info->screen.font, &textarea, "X Y Z");

	SDL_RenderPresent(info->renderer);
}
