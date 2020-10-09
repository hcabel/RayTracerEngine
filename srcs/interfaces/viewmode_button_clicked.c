/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewmode_button_clicked.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:26:50 by hcabel            #+#    #+#             */
/*   Updated: 2020/10/09 10:31:57 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		set_lit_viewmode(t_info *info)
{
	if (info->scene.cam.viewmode != 0)
	{
		info->scene.cam.viewmode = 0;
		return (GOOD);
	}
	return (FAILED);
}

int		set_unlit_viewmode(t_info *info)
{
	if (info->scene.cam.viewmode != 1)
	{
		info->scene.cam.viewmode = 1;
		return (GOOD);
	}
	return (FAILED);
}

int		set_normalmap_viewmode(t_info *info)
{
	if (info->scene.cam.viewmode != 2)
	{
		info->scene.cam.viewmode = 2;
		return (GOOD);
	}
	return (FAILED);
}

int		set_iteration_viewmode(t_info *info)
{
	if (info->scene.cam.viewmode != 3)
	{
		info->scene.cam.viewmode = 3;
		return (GOOD);
	}
	return (FAILED);
}
