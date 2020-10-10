/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 18:02:11 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	witch_viewmode_button_clicked(t_vector2d loc, t_info *info)
{
	unsigned int	i;

	loc.x -= info->screen.viewmode.area.x;
	loc.y -= info->screen.viewmode.area.y;
	i = 0;
	while (i < info->screen.viewmode.scrollbox.amount)
	{
		if (aabb(info->screen.viewmode.scrollbox.list[i].area, loc) == GOOD)
			return (info->screen.viewmode.scrollbox.list[i].clicked(info));
		else
			i++;
	}
	return (FAILED);
}

static int	viewport_clicked(t_vector2d loc, t_info *info)
{
	unsigned int	i;
	t_vector		dir;
	t_ray_hit		ray;

	loc.x -= info->screen.viewport.image.x;
	loc.y -= info->screen.viewport.image.y;
	dir = get_ray_direction_from_coordinate(loc, &info->scene.cam,
		info->screen.viewport.image.w, info->screen.viewport.image.h);
	ray = trace_ray(&info->scene, info->scene.cam.location, dir, VIEW_DISTANCE);
	if (ray.hit.bool == 1)
	{
		if (info->scene.target != NULL)
			((t_object*)info->scene.target)->istarget.bool = 0;
		ray.hit_object->istarget.bool = 1;
		info->scene.target = ray.hit_object;
		info->scene.target_type = 1;
		return (GOOD);
	}
	if (info->scene.target != NULL && info->scene.target_type == 1)
		((t_object*)info->scene.target)->istarget.bool = 0;
	info->scene.target = NULL;
	info->scene.target_type = 0;
	return (GOOD);
}

static int	witch_panel_clicked(t_vector2d loc, t_info *info)
{
	int	updateviewport;

	updateviewport = FAILED;
	if (aabb(info->screen.viewmode.area, loc) == GOOD)
		updateviewport = witch_viewmode_button_clicked(loc, info);
	else if (aabb(info->screen.viewport.area, loc) == GOOD)
		updateviewport = viewport_clicked(loc, info);
	return (updateviewport);
}

void		mouse_press_input(t_bool *quit, t_info *info, SDL_Event *event)
{
	int			updateviewport;
	t_vector2d	mouse_location;

	mouse_location.x = event->motion.x;
	mouse_location.y = event->motion.y;
	updateviewport = FAILED;
	if (event->button.button == SDL_BUTTON_LEFT)
		updateviewport = witch_panel_clicked(mouse_location, info);
	if (updateviewport == GOOD)
	{
		info->screen.resolution = FIRST_RESOLUTION;
		draw_calls_add(info, DRAWCALL_VIEWPORT);
	}
}
