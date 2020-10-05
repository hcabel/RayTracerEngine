/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:44:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/05 18:40:40 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	initcam(t_cam *cam)
{
	cam->location = new_vector(0, 0, 0);
	cam->rotation = new_vector2d(0, 0);
}

void	initlight(t_light *light)
{
	light->location = new_vector(0, 0, 0);
	light->rotation = new_vector2d(0, 0);
	light->intensity = 1;
}

void	initobject(t_object *obj)
{
	obj->location = new_vector(0, 0, 0);
	obj->rotation = new_vector2d(0, 0);
	obj->scale = new_vector(1, 1, 1);
	obj->color = new_vector(255, 255, 255);
	//obj->sdffunction = sdf_shere;
}
