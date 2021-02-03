/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:58:59 by hcabel            #+#    #+#             */
/*   Updated: 2021/01/29 16:59:11 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	convert_shapes_to_kernel_list(t_object *list, unsigned int amount,
				t_kernel_shape **newlist)
{
	unsigned int	index;

	if (!(*newlist = (t_kernel_shape*)malloc(sizeof(t_kernel_shape) * amount)))
		return (MALLOC_ERROR);
	index = 0;
	while (index < amount)
	{
		(*newlist)[index].location = list[index].location;
		(*newlist)[index].rotation = list[index].rotation;
		(*newlist)[index].scale = list[index].scale;
		(*newlist)[index].color = list[index].color;
		(*newlist)[index].sdf_index = list[index].sdf_index;
		(*newlist)[index].istarget = list[index].istarget;
		index++;
	}
	return (GOOD);
}

static int	convert_light_to_kernel_list(t_light *list, unsigned int amount,
				t_kernel_light **newlist)
{
	unsigned int	index;

	if (!(*newlist = (t_kernel_light*)malloc(sizeof(t_kernel_light) * amount)))
		return (MALLOC_ERROR);
	index = 0;
	while (index < amount)
	{
		(*newlist)[index].location = list[index].location;
		(*newlist)[index].rotation = list[index].rotation;
		(*newlist)[index].intensity = list[index].intensity;
		index++;
	}
	return (GOOD);
}

int			convert_scene_to_kernel_scene(t_kernel_args *kernel_args,
				t_info *info, unsigned int numpixel)
{
	kernel_args->scene.cam_location = info->scene.cam.location;
	kernel_args->scene.cam_rotation = info->scene.cam.rotation;
	kernel_args->scene.viewmode = info->scene.cam.viewmode;
	kernel_args->scene.shapes_num = info->scene.shapes_amount;
	kernel_args->scene.lights_num = info->scene.light_amount;
	kernel_args->scene.img_x = info->screen.viewport.image.x;
	kernel_args->scene.img_y = info->screen.viewport.image.y;
	kernel_args->scene.img_w = info->screen.viewport.image.w;
	kernel_args->scene.img_h = info->screen.viewport.image.h;
	if (convert_shapes_to_kernel_list(info->scene.shapes,
		info->scene.shapes_amount, &kernel_args->shapes) != GOOD)
		return (MALLOC_ERROR);
	if (convert_light_to_kernel_list(info->scene.lights,
		info->scene.light_amount, &kernel_args->lights) != GOOD)
		return (MALLOC_ERROR);
	return (GOOD);
}
