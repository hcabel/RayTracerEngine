/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/11/03 12:21:36 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	viewport_clicked(t_vector2d loc, t_info *info)
{
	unsigned int	i;
	t_vector		dir;
	t_ray_hit		ray;
	int				result;

	loc.x -= info->screen.viewport.area.x;
	loc.y -= info->screen.viewport.area.y;
	loc.x /= info->screen.viewport.resolution;
	loc.y /= info->screen.viewport.resolution;
	result = FAILED;
	dir = get_ray_direction(loc, info->scene.cam.rotation, 90,
		info->screen.viewport.image);
	ray = trace_ray(&info->scene, info->scene.cam.location, dir, VIEW_DISTANCE);
	if (ray.hit.bool == 1)
	{
		if (ray.hit_object->istarget.bool != 1)
			result = GOOD;
		if (info->scene.target != NULL)
			((t_object*)info->scene.target)->istarget.bool = 0;
		ray.hit_object->istarget.bool = 1;
		info->scene.target = ray.hit_object;
		info->scene.target_type = 1;
		return (result);
	}
	if (info->scene.target != NULL)
			result = GOOD;
	if (info->scene.target != NULL && info->scene.target_type == 1)
		((t_object*)info->scene.target)->istarget.bool = 0;
	info->scene.target = NULL;
	info->scene.target_type = 0;
	return (result);
}

static int	witch_panel_clicked(t_vector2d loc, t_info *info)
{
	int	updateviewport;

	updateviewport = FAILED;
	if (aabb(info->screen.viewmode.area, loc) == GOOD)
		updateviewport = press_on_viewmode_panel(loc, info);
	else if (aabb(info->screen.viewport.area, loc) == GOOD)
		updateviewport = viewport_clicked(loc, info);
	else if (aabb(info->screen.details.area, loc) == GOOD)
		updateviewport = press_on_details_panel(loc, info);
	return (updateviewport);
}

void		mouse_press_input(t_bool *quit, t_info *info, SDL_Event *event)
{
	int			updateviewport;
	t_vector2d	mouse_location;

	mouse_location.x = event->motion.x;
	mouse_location.y = event->motion.y;
	updateviewport = FAILED;


	if (event->button.button == SDL_BUTTON_LEFT
		&& event->type == SDL_MOUSEBUTTONUP)
	{
		if (info->mouse.is_dragged.bool == 1)
		{
			info->mouse.is_dragged.bool = 0;
			printf("DRAG off\n");
		}
		else
			updateviewport = witch_panel_clicked(mouse_location, info);
	}
	else if (event->button.button == SDL_BUTTON_LEFT
		&& event->type == SDL_MOUSEBUTTONDOWN
		&& event->button.clicks == 2
		&& info->scene.target != NULL)
	{
		printf("DRAG on\n");
		info->mouse.is_dragged.bool = 1;
		info->mouse.startloc = mouse_location;
		info->mouse.target_base_3dvector =
			((t_object*)info->scene.target)->location;
	}

	if (updateviewport == GOOD)
	{
		info->screen.viewport.resolution = FIRST_RESOLUTION;
		draw_calls_add(info, DRAWCALL_VIEWPORT);
		draw_calls_add(info, DRAWCALL_DETAILS_PANEL);
	}
}
