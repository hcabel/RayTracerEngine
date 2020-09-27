/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:44:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/27 11:49:09 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	initcam(t_cam *cam)
{
	cam->location = newvector(0, 0, 0);
	cam->rotation = newvector2d(0, 0);
}

void	initlight(t_light *light)
{
	light->location = newvector(0, 0, 0);
	light->rotation = newvector2d(0, 0);
	light->intensity = 1;
}

void	initobject(t_object *obj)
{
	obj->location = newvector(0, 0, 0);
	obj->rotation = newvector2d(0, 0);
	obj->scale = newvector(1, 1, 1);
	obj->color = newvector(255, 255, 255);
	//obj->sdffunction = sdf_shere;
}
