/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_selector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 14:23:43 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/24 16:42:25 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			check_for_hidden_obj(t_light *light, t_vector dir,
						float prec, t_vector loc)
{
	t_vector		tmp;

	tmp = vector_normalize(vector_subtract(light->location,
		loc));
	if (tmp.x + prec >= dir.x && tmp.x - prec <= dir.x
		&& tmp.y + prec >= dir.y && tmp.y - prec <= dir.y
		&& tmp.z + prec >= dir.z && tmp.z - prec <= dir.z)
		return (1);
	return (0);
}

unsigned int	shape_selector_display(t_vector2d loc, t_info *info)
{
	t_vector	dir;

	t_light		lights;
	t_cam		cam;
	t_object	obj;
	t_scene		scene;

	if (info->scene.target == NULL)
		return (0);

	cam.location = new_vector(0, 1.5, -3);
	cam.rotation = new_vector2d(-0.5, 0);
	cam.viewmode = 0;
	scene.cam = cam;
	scene.light_amount = 1;
	scene.shapes_amount = 1;
	scene.sdf_list[0] = info->scene.sdf_list[0];
	scene.sdf_list[1] = info->scene.sdf_list[1];
	scene.sdf_list[2] = info->scene.sdf_list[2];
	scene.sdf_list[3] = info->scene.sdf_list[3];
	scene.sdf_list[4] = info->scene.sdf_list[4];
	obj.location = new_vector(0, 0, 0);
	obj.rotation = new_vector2d(0, 0);
	obj.sdf_index = ((t_object*)info->scene.target)->sdf_index;
	obj.color = ((t_object*)info->scene.target)->color;
	obj.scale = new_vector(1,1,1);
	scene.shapes = &obj;
	lights.location = new_vector(0, 2, -3);
	lights.intensity = 100;
	lights.rotation = new_vector2d(0, 0);
	scene.lights = &lights;
	dir = get_ray_direction(loc, cam.rotation, 60,
		info->screen.details.shape_selector.area);
	return (raymarching(&scene, dir));
}

int		increase_target_shape(t_info *info)
{
	unsigned int	tmp;

	if (info->scene.target == NULL)
		return (FAILED);
	tmp = ((t_object*)info->scene.target)->sdf_index;
	if (tmp < 4)
		((t_object*)info->scene.target)->sdf_index = tmp + 1;
	else
		((t_object*)info->scene.target)->sdf_index = 0;
	return (GOOD);
}

int		decrease_target_shape(t_info *info)
{
	unsigned int	tmp;

	if (info->scene.target == NULL)
		return (FAILED);
	tmp = ((t_object*)info->scene.target)->sdf_index;
	if (tmp > 0)
		((t_object*)info->scene.target)->sdf_index = tmp - 1;
	else
		((t_object*)info->scene.target)->sdf_index = 4;
	return (GOOD);
}
