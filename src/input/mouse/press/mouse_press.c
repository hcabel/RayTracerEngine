/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:29:51 by hcabel            #+#    #+#             */
/*   Updated: 2020/12/31 13:51:01 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	viewport_clicked(t_vector2d loc, t_info *info)
{
	/*unsigned int	i;
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
		if (ray.hit_object->istarget != 1)
			result = GOOD;
		if (info->scene.target != NULL)
			((t_object*)info->scene.target)->istarget = 0;
		ray.hit_object->istarget = 1;
		info->scene.target = ray.hit_object;
		info->scene.target_type = 1;
		return (result);
	}
	if (info->scene.target != NULL)
			result = GOOD;
	if (info->scene.target != NULL && info->scene.target_type == 1)
		((t_object*)info->scene.target)->istarget = 0;
	info->scene.target = NULL;
	info->scene.target_type = 0;*/
	return (0);
}

void		mouse_press(int *quit, t_info *info, SDL_Event *event)
{
	int	result;

	result = 0;

	if (aabb(info->screen.top.area, info->mouse.location) == GOOD)
		result |= press_on_top_panel(info->mouse.location, info);
	else if (aabb(info->screen.viewport.area, info->mouse.location) == GOOD)
		result |= viewport_clicked(info->mouse.location, info);
	else if (aabb(info->screen.left.area, info->mouse.location) == GOOD)
		result |= press_on_left_panel(info->mouse.location, info);

	if (result > 0)
	{
		if ((result & 1) != 0)
		{
			info->screen.viewport.resolution = FIRST_RESOLUTION;
			drawcall_add(info, DRAWCALL_VIEWPORT);
		}
		if (((result >> 1) & 1) != 0)
			drawcall_add(info, DRAWCALL_TOP_PANEL);
		if (((result >> 2) & 1) != 0)
			drawcall_add(info, DRAWCALL_LEFT_PANEL);
		if (((result >> 3) & 1) != 0)
			drawcall_add(info, DRAWCALL_CHECK_VIEWPORT);
	}
}
