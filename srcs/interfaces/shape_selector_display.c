/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_selector_display.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 14:23:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/10 18:32:47 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int	shape_selector_display(t_vector2d loc, t_info *info)
{
	t_ray_hit	ray;
	t_vector	dir;
	t_vector	color;

	if (info->scene.target == NULL)
		return (0x0);
	dir = get_ray_direction(loc, new_vector2d(-1, 0),
		info->screen.details.shape_selector.area);
	ray = trace_ray_simplified(new_vector(0, 2, -1.5), dir, info->scene.target);
	color = new_vector(0, 0, 0);
	if (ray.hit.bool == 1)
	{
		color.x = ray.hit_object->color.x;
		color.y = ray.hit_object->color.y;
		color.z = ray.hit_object->color.z;
	}
	return (((int)color.x << 24) + ((int)color.y << 16) + ((int)color.z << 8)
		+ 0xFF);
}
