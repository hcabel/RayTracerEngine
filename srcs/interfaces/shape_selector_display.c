/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_selector_display.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 14:23:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/11 19:54:18 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int	shape_selector_display(t_vector2d loc, t_info *info)
{
	t_ray_hit	ray;
	t_vector	dir;
	t_vector	color;
	float		intensity;
	t_light		lights[1];

	if (info->scene.target == NULL)
		return (0x0);
	dir = get_ray_direction(loc, new_vector2d(-1, 0),
		info->screen.details.shape_selector.area);
	ray = trace_ray_simplified(new_vector(0, 2, -1.5), dir, info->scene.target);
	color = new_vector(0, 0, 0);
	if (ray.hit.bool == 1)
	{
		lights[0].location = new_vector(-3, 3, -3);
		lights[0].intensity = 100;
		lights[0].rotation = new_vector2d(0, 0);
		intensity = get_light_intensity(&info->scene, ray.location,
			info->scene.target, dir, lights);
		color.x = ray.hit_object->color.x * intensity;
		color.y = ray.hit_object->color.y * intensity;
		color.z = ray.hit_object->color.z * intensity;
	}
	return (((int)color.x << 24) + ((int)color.y << 16) + ((int)color.z << 8)
		+ 0xFF);
}
