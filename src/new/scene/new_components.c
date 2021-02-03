/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_components.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 20:04:31 by hcabel            #+#    #+#             */
/*   Updated: 2021/02/02 14:56:30 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam		new_cam(void)
{
	t_cam	cam;

	cam.viewmode = 0;
	cam.location = new_vector(0, 0, 0);
	cam.rotation = new_vector2d(0, 0);
	return (cam);
}

t_light		new_light(void)
{
	t_light	light;

	light.location = new_vector(0, 0, 0);
	light.rotation = new_vector2d(0, 0);
	light.intensity = 1;
	return (light);
}

t_object	new_object(void)
{
	t_object	obj;

	obj.location = new_vector(0, 0, 0);
	obj.rotation = new_vector2d(0, 0);
	obj.scale = new_vector(1, 1, 1);
	obj.color = new_vector(255, 255, 255);
	obj.istarget = 0;
	obj.sdf_index = 0;
	return (obj);
}
