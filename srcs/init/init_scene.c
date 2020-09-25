/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 14:44:16 by hcabel            #+#    #+#             */
/*   Updated: 2020/09/25 15:32:41 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		initcam(t_cam *cam)
{
	cam->location = newvector(0, 0, 0);
	cam->rotation = newvector2d(0, 0);
}

int		initlight(t_light *light)
{
	light->location = newvector(0, 0, 0);
	light->rotation = newvector2d(0, 0);
	light->intensity = 1;
}

int		initobject(t_object *obj)
{
	obj->location = newvector(0, 0, 0);
	obj->rotation = newvector2d(0, 0);
	obj->scale = newvector(1, 1, 1);
	//obj->sdffunction = sdf_shere;
}
